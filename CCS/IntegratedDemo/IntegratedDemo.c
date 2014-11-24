#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include <Dsplib.h>
#include <sar.h>


#include "XVGA.h"
#include "noise_gate.h"
#include "FFT.h"
#include "tunable_filter.h"
#include "LED.h"
#include "AdaptiveNotch.h"

#define FOREVER 1
#define PI 3.14159265


Uint32 Counter;

DATA bOne	[2*FFTSIZE];//Buffer 1
DATA bTwo 	[2*FFTSIZE];//Buffer 2
DATA bOut	[2*FFTSIZE];//Buffer 3--FFT output goes here.


void Reset();

Int16 output;
Uint8 gateOn, filterOn;


interrupt void I2S_ISR()
{
	Int16 x[1];
	Int16  left;
	//AIC_read2(&left,x);
	AIC_read2(x,&left);
	AIC_write2(output,output);

	output = left;

	if(gateOn)
	{
		output = noise_gate_default(left);
	}

	if(filterOn)
	{

		output = applyNotches(output);
	}


	queueFFT(output);

	IFR0 &= (1 << I2S_BIT_POS);//Clear interrupt Flag
}



// Setup AIC interrupt routine.
void I2S_interrupt_setup(void)
{
	Uint32 reset_loc = (Uint32)Reset;
	IVPD = reset_loc >> 8;//pointer table points to Reset
	IVPH = reset_loc >> 8;//Ditto

	*((Uint32*)((reset_loc + I2S_ISR_OFFSET)>>1)) = (Uint32)I2S_ISR;

	SYS_EXBUSSEL |= (0x1 << 8);//Set the External bus select SP0Mode to I2S
	IER0 |= (1 << I2S_BIT_POS);//Set up the Global interrupt register to flag on I2S receive flag
	IFR0 &= (1 << I2S_BIT_POS);
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void main(void)
{
    // For switching
    Uint16 key;
	gateOn = 0;
	filterOn = 0;

	// For keeping track of max values of FFT
    Int32 maxIndex, max;

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	My_LED_init();
   	AIC_init();
   	I2S_interrupt_setup();
    InitSpi();
    initFFT(bOne, bTwo, bOut);
    initNotches();
	_enable_interrupts();

	unsigned int start_switch = 1;


    while(FOREVER)
    {
    	key = Get_Key_Human();
		if(key == SW1)
		{
			toggle_LED(0);
			// Reset audio filters
			filterOn = 1 - filterOn;
			if(!filterOn)
			{
				initNotches();
			}
		}
		else if(key == SW2)
		{
			toggle_LED(1);
			gateOn = 1 - gateOn;
		}

		if(FFTready())
		{
			// ---- Take FFT ----
			processFFT();

			// ---- Update display ----
			XVGAinit(start_switch);
		    drawThreshold();
		    drawNotches();
			showFFT(&maxIndex, &max); // extract max value and index
			start_switch = 0;

			// ---- Adjust notch filters if needed ----
			if(filterOn)
			{
				stepNotch(max, maxIndex);
			}
		}
    }

        TERMINATE:
        	// Won't run ;P
        	printf("CRASHED!\n");

}

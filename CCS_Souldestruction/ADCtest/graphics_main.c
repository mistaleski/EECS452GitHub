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

#define FOREVER 1
#define PI 3.14159265

#define ADCBUSY 0x8000

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

		output = applyNotches(&output);
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

static const Uint16 addrs[5] = {0x3C00, 0x0C00, 0x1C00, 0x2C00, 0x5C00};

// @param data is the array to be filled with ADC values. Min size 4*sizeof(Uint16).
void Read_all(Uint16 *data)
{
    Uint16 val, i, j,failsafe;

	// Poll each channel
	for(i=0; i<4; ++i )
	{

		failsafe = 1000;
		// Wait for previous conversion to finish
		while((*SARDATA) & ADCBUSY);

		*SARCTRL = 0x0C00 + ((i+2) & 7) << 12;//(void*)(addrs[i]);

		*SARCTRL |= 0x8000;

		while(!((*SARDATA) & ADCBUSY))
		{
				if(!(--failsafe))
				{
					break;
				}
		}

		// Wait for conversion to finish
		while((*SARDATA) & ADCBUSY);

		// Get data
		data[i] = (*SARDATA) & 0x03FF;
		*SARCTRL &= ~0x8000;

		for(j=0; j<1000; ++j)
		{
			asm("	nop");
		}
	}
}


Uint16 readCh3(void)//Faster but less acurate ok for Human interaction not ADC
{
	Uint16 val;
	*SARCTRL = 0xB800;
	val = *SARDATA;


	return val;

}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void main(void)
{
    int i;

    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	My_LED_init();
   	I2S_interrupt_setup();
    InitSpi();
    Init_SAR();

    Uint16 data[4];

    *SARPINCTRL &= ~0x8000;

    while(FOREVER)
    {
    	Read_all(data);
    	printf("%05d\t%05d\t%05d\t%05d\n\n", data[0],data[1],data[2],data[3]);
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

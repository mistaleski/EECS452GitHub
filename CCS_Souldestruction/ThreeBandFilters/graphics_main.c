#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include "tunable_filter.h"
#include <sar.h>
#include "LED.h"

#define FOREVER 1
#define PI 3.14159265

#define SARCTRL      ((ioport volatile unsigned*)0x7012)
#define SARDATA      ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

#define ADCBUSY 0x8000

#define NUM_FILTERS 5

Int16 output;
Int16 biq[6 * NUM_FILTERS];
Int16 myBuff[4 * NUM_FILTERS];
Int32 scale[5];

void Reset();

interrupt void I2S_ISR()
{
	int i;
	Int16 x[1];
	Int16  left = 0;

	AIC_read2(x,&left);
	AIC_write2(output,output);

	output = 0;
	for(i=0; i<NUM_FILTERS; ++i)
	{
		output += (((Int32)(IIR_DF1(left, &biq[i*BIQ_COEFF], &myBuff[i*4]) >> 2))*scale[i]) >> 10;
	}

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

// @param data is the array to be filled with ADC values. Min size 4*sizeof(Uint16).
void Read_all(Uint16 *data)
{
    Uint16 i, j,failsafe;

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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


void main(void)
{
    int i, j;
    Uint16 data[4];

    // unity gain
    for(i=0; i<NUM_FILTERS; ++i)
    {
    	scale[i] = 408;
    }

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	I2S_interrupt_setup();
   	Init_SAR();
   	My_LED_init();
   	_enable_interrupts();

   	output = 0;

   	*SARPINCTRL &= ~0x8000;

   	for(i=0; i<NUM_FILTERS; ++i)
   	{
   		redefineFilter(i, &biq[i*BIQ_COEFF]);
   	}

    while(FOREVER)
    {
    	Read_all(data);
        //for(i=0; i<NUM_FILTERS; ++i)
        //{
        //	scale[i] = data[0];
        //}
    	scale[0] = data[0]; // Bass
    	scale[2] = data[2]; // Mid
    	scale[4] = data[3]; // Treble

    	toggle_LED(0);
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

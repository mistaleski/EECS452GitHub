#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>

#include "tunable_filter.h"
#include "tunable_ThreeBandfilter.h"

#define FOREVER 1
#define PI 3.14159265

#define ADCBUSY 0x8000

void Reset();

Int16 output;
Uint8 gateOn, filterOn;



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

		*SARCTRL = 0x0C00 + ((i+2) & 7) << 12;

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

//interrupt void I2S_ISR()
//{
	// won't run
//}

Uint16 readCh3(void)//Faster but less acurate ok for Human interaction not ADC
{
	Uint16 val;
	*SARCTRL = 0xB800;
	val = *SARDATA;


	return val;

}

// Setup AIC interrupt routine.
void I2S_interrupt_setup(void)
{
	Uint32 reset_loc = (Uint32)Reset;
	IVPD = reset_loc >> 8;//pointer table points to Reset
	IVPH = reset_loc >> 8;//Ditto

	//*((Uint32*)((reset_loc + I2S_ISR_OFFSET)>>1)) = (Uint32)I2S_ISR;

	SYS_EXBUSSEL |= (0x1 << 8);//Set the External bus select SP0Mode to I2S
	IER0 |= (1 << I2S_BIT_POS);//Set up the Global interrupt register to flag on I2S receive flag
	IFR0 &= (1 << I2S_BIT_POS);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void main(void)
{
    int i;
	Int16 x[1];
	Int16  left;
	Int16 output;

    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	My_LED_init();
    InitSpi();
    Init_SAR();
    I2S_interrupt_setup();

    //Uint16 data[4];
    Int16 temp;

    Int16 scale[5] = {1,1,1,1,1};

#define EQ3_NUM_FILTS 5
    Int16 buffs[4*EQ3_NUM_FILTS];
    Int16 biq[6*EQ3_NUM_FILTS]; // biquads of all 5 filters

    for(i=0; i<5; ++i)
    {
    	redefineFilter2(i, &biq[i*BIQ_COEFF]);
    }

    *SARPINCTRL &= ~0x8000;

    while(FOREVER)
    {
    	output = 0;
    	AIC_read2(x,&left);
    	for(i=0; i<1; ++i)
        {
        	temp = ((IIR_DF1_2(left, &biq[i*BIQ_COEFF], &buffs[i*4])));//*Adjust[i]) >> 15;
        	output = temp;
        	//output += (scale[i]*temp)/EQ3_NUM_FILTS;
        }
    	AIC_write2(output,output);
    }

}

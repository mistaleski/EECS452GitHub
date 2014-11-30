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

static const Int16 _biq[6] = {8192, 0, -8192, 8192, -15883, 7692};
Int16 delay_buff[4];

#define B0 ((Int32)_biq[0])
#define B1 ((Int32)_biq[1])
#define B2 ((Int32)_biq[2])
#define A0 ((Int32)_biq[3])
#define A1 ((Int32)_biq[4])
#define A2 ((Int32)_biq[5])

Int16 _IIR(Int16 input) {
	Int16 y;
	Int32 Acc;

		Acc = ((Int32)input) * B0 + ((Int32)(delay_buff[0])) * B1 + \
				((Int32)(delay_buff[1])) * B2 - ((Int32)(delay_buff[2])) * A1 - \
				((Int32)(delay_buff[3])) * A2;
				// takes the 16-bit Q15 values from the input
				// and Z-1 blocks and multiply them by the 16-bit Q13 coeffs
				// to get a 32-bit Q28.

		Int32 temp42 = Acc >> 16;
		Acc = temp42 > 32767 ? 32767 : temp42 < -32768 ? -32768 : temp42; // Converts to a 16-bit Q15 with rounding and saturation.

		//updates the various delay blocks
		delay_buff[1]	=  delay_buff[0];
		delay_buff[0]	=  input;
		delay_buff[3]	= delay_buff[2];
		delay_buff[2]	= (Int16)Acc;

		y = (Int16)Acc;

	return y;
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
    Int32 temp;

    Int16 scale[5] = {1,1,1,1,1};

#define EQ3_NUM_FILTS 5
    Int16 buffs[4*EQ3_NUM_FILTS];
    Int16 biq[6*EQ3_NUM_FILTS]; // biquads of all 5 filters

    for(i=0; i<5; ++i)
    {
    	redefineFilter2(i, &biq[i*BIQ_COEFF]);
    }

    // debug
    initNotches();

    *SARPINCTRL &= ~0x8000;

    while(FOREVER)
    {
    	output = 0;
    	AIC_read2(x,&left);
    	output = _IIR(left);
    	//output = IIR_DF1_2(left, &biq[0], &buffs[0]);
    	//for(i=0; i<5; ++i)
        //{
        //	temp = (((Int32)IIR_DF1_2(left, &biq[i*BIQ_COEFF], &buffs[i*4])));//*Adjust[i]) >> 15;
        //	output += (scale[i]*temp)/EQ3_NUM_FILTS;
        //}
    	AIC_write2(output,output);
    }

}

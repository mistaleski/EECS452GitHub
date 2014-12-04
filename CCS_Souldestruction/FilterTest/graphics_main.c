#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include "tunable_filter.h"

#define FOREVER 1
#define PI 3.14159265


Uint32 Counter;


void Reset();

Int16 output;

interrupt void I2S_ISR()
{
	// do nothing
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
    int i;

	Int16 x[1];
	Int16  left = 0;
	Int16  output = 0;
	Int16  temp = 0;
	Int16  temp2 = 0;
	Int16 biq[6],biq2[6];
	Int16 myBuff[4]  = {{0}};
	Int16 myBuff2[4] = {{0}};
	Int32 myFilter[6] = {
			8,
			 17,
			 8,
			 32767,
			 -64682,
			 31947
	};

	Int32 myFilter2[6] = {
			8,
			 16,
			 8,
			 32767,
			 -63557,
			 30822
	};

	Int32 adjust = 32768;

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	I2S_interrupt_setup();


	biq[0] =  (Int16)(myFilter[0] >> 1);		//b0
	biq[1] =  (Int16)(myFilter[1] >> 1);		//b1
	biq[2] =  (Int16)(myFilter[2] >> 1);		//b2

	biq[3] =  (Int16)(myFilter[3] >> 1);		//a0  -- this one is actually ignored.
	biq[4] =  (Int16)(myFilter[4] >> 1);		//a1
	biq[5] =  (Int16)(myFilter[5] >> 1);		//a2

	biq2[0] =  (Int16)(myFilter2[0] >> 1);		//b0
	biq2[1] =  (Int16)(myFilter2[1] >> 1);		//b1
	biq2[2] =  (Int16)(myFilter2[2] >> 1);		//b2

	biq2[3] =  (Int16)(myFilter2[3] >> 1);		//a0  -- this one is actually ignored.
	biq2[4] =  (Int16)(myFilter2[4] >> 1);		//a1
	biq2[5] =  (Int16)(myFilter2[5] >> 1);		//a2

		output = 0;
		temp = 0;
		temp2 = 0;

//#define PASSTHROUGH

    while(FOREVER)
    {

    	AIC_read2(x,&left);
    	AIC_write2(output,output);
#ifdef PASSTHROUGH
    	output = left;
#else
    	left = 9132;
    	/*temp*/ output = (IIR_DF1(left, biq, myBuff));
    	//output = (IIR_DF1(temp, biq2, myBuff2));
   	//output = (((Int32)temp2) * adjust) >> 15;
#endif
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

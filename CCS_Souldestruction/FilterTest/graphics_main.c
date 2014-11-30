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
	Int16 biq[6];
	Int16 myBuff[4];
	Int32 myFilter[6] = {13044, -1, -13046, 32767, 17886, 4313};

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

		output = 0;

    while(FOREVER)
    {

    	AIC_read2(x,&left);
    	//output = left;
    	output = IIR_DF1(left, biq, myBuff);
    	AIC_write2(output,output);
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

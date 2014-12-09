#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include "tunable_SixBandfilter.h"
#include <Dsplib.h>
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



Int16 output;
Int16 biq[BIQ_COEFF * NUM_BIQUADS];
Int16 myBuff[4];
Int32 scale[NUM_FILTERS];

void Reset();

interrupt void I2S_ISR()
{
	int i;
	Int16 x[1];
	Int16  left = 0;
	Int16 in;
	Int16 temp16;
	Int32 temp32;


	AIC_read2(x,&left);
	AIC_write2(output,output);

	in = 9132;//left;

	output = 0;
	//for(i=0; i<1; ++i)
	//{
		Uint8 flag = iircas51(&in, biq, &output, myBuff, 1, 1);
		if(flag == 1)
		{
			while(1);
		}
		//output = temp16;
		//temp32 = ((temp32*adjust[i]) >> 15); // Filter Internal Scale
		//temp32 = ((temp32*scale[i]) >> 15); // User Scale
		//output += (Int16)(temp32 >> 4);
	//}

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

Int32 myFilter[6] = //{8191, 16383, 8191, 32767, -59487, 27229};
{
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

void main(void)
{
    int i, j;
    Uint16 data[4];

    for(i=0; i<4; ++i)
    {
    	myBuff[i] = 0;
    }

    // unity gain
    for(i=0; i<NUM_FILTERS; ++i)
    {
    	scale[i] = 13045;
    }

    scale[0] = 32768;

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	//My_LED_init();
   	I2S_interrupt_setup();
   	_enable_interrupts();

   	output = 0;

   	*SARPINCTRL &= ~0x8000;

   //	for(i=0; i<NUM_FILTERS; ++i)
   //	{
   //		redefineFilter(i, &biq[i*BIQ_COEFF*2]);
   //	}

	biq[0] =  (Int16)(myFilter[0] >> 1);		//b0
	biq[1] =  (Int16)(myFilter[1] >> 1);		//b1
	biq[2] =  (Int16)(myFilter[2] >> 1);		//b2
	biq[3] =  (Int16)(myFilter[4] >> 1);		//a1
	biq[4] =  (Int16)(myFilter[5] >> 1);		//a2

	biq[5] =  (Int16)(myFilter2[0] >> 1);		//b0
	biq[6] =  (Int16)(myFilter2[1] >> 1);		//b1
	biq[7] =  (Int16)(myFilter2[2] >> 1);		//b2
	biq[8] =  (Int16)(myFilter2[4] >> 1);		//a1
	biq[9] =  (Int16)(myFilter2[5] >> 1);		//a2

	Uint8 filtNum = 0;
   	Uint8 key;

    while(FOREVER)
    {
    	/*
    	key = Get_Key_Human();
		if(key == SW1)
		{
			toggle_LED(0);
			switch(scale[filtNum])
			{
				case 0:
					scale[filtNum] = 13045;
					break;
				case 13045:
					scale[filtNum] = 32768;
					break;
				case 32768:
					scale[filtNum] = 0;
					break;
				default:
					scale[filtNum] = 13045;
			}
		}
		else if(key == SW2)
		{
			toggle_LED(1);
			filtNum = filtNum + 1;
			if(filtNum >= NUM_FILTERS)
			{
				filtNum = 0;
			}
		}

		for(i=0; i<10000; ++i)
		{
			for(j=0; j<100; ++j)
			{
				asm("	nop");
			}
		}
		*/
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

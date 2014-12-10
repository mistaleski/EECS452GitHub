#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include "tunable_SixBandfilter.h"
#include "LED.h"

#define FOREVER 1
#define PI 3.14159265

#define SARCTRL      ((ioport volatile unsigned*)0x7012)
#define SARDATA      ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

Int16 output;
Int16 biq[2 * 6 * NUM_FILTERS];
Int16 myBuff[2 * 4 * NUM_FILTERS];
Int32 scale[NUM_FILTERS];

//#define COUNT1START 16383
//#define COUNT2START 10
//int blah, countdown, countdown2;

void Reset();

interrupt void I2S_ISR()
{
	volatile int i;
	Int16 x[1], temp, temp2;
	Int16  left = 0;

	AIC_read2(x,&left);
	AIC_write2(output,output);

	output = 0;
	for(i=0; i<NUM_FILTERS; ++i)
	{
		temp = (((Int32)(IIR_DF1(left, &biq[2*i*BIQ_COEFF], &myBuff[2*i*4]))));
		temp2 = (((Int32)(IIR_DF1(temp, &biq[(2*i + 1)*BIQ_COEFF], &myBuff[(2*i + 1)*4])))*adjust[i]) >> 14;
		output += (((Int32)temp2) * scale[i]) >> 15;
	}
//
//	if(!()--countdown2))
//	{
//		if(!(--countdown))
//		{
//			blah = blah + 1;
//			if(blah > 5) blah = 0;
//			countdown = COUNT1START;
//			toggle_LED(0);
//		}
//		countdown2 = COUNT2START;
//	}

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
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%7



void main(void)
{
    int i, j;

//    blah = 0;
//    countdown = COUNT1START;
//    countdown2 = COUNT2START;

    // unity gain

    for(i=0; i<NUM_FILTERS; ++i)
    {
    	scale[i] = 4096;
    }

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	I2S_interrupt_setup();
   	My_LED_init();
   	_enable_interrupts();

   	output = 0;

   	for(i=0; i<NUM_FILTERS; ++i)
   	{
   		redefineFilter((Uint16)i, &biq[2*i*BIQ_COEFF]);
   	}

    while(FOREVER)
    {
    	//Read_all(data);

    	//scale[0] = data[0];
    	//scale[2] = data[2];
    	//scale[4] = data[3];
    	//scale[0] = Coeff[0] + (Coeff[1]*(Uint32)data[0]); // Bass
    	//scale[2] = Coeff[0] + (Coeff[2]*(Uint32)data[2]); // Mid
    	//scale[4] = Coeff[0] + (Coeff[2]*(Uint32)data[3]); // Treble

    	//toggle_LED(0);
    }

        TERMINATE:
        	printf("CRASHED!\n");

}

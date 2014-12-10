#include <usbstk5515.h>
#include <AIC_func.h>
#include <stdio.h>
#include <math.h>
#include <usbstk5515_interrupts.h>
//#include "cheby100N512.h"
#include <Dsplib.h>
#include "XVGA.h"
#include "recordSweep.h"
#include "avgFFT512to6.h"
//#include "FFT.h"
#include "tunable_SixBandfilter.h"
#include <sar.h>
#include "LED.h"

#define FOREVER 1
#define BLUE 2
#define PI 3.14159265

#define TABLE_SIZE  512

void XVGAinit(Uint16);
void GoTo(Uint16 x, Uint16 y);
void Draw(Uint16 color, Uint16 x, Uint16 y);
void InitSpi(void);		// added
void InitSystem(void);	// added
void ConfigPort(void);	// added


#define BUFSIZE 16384
#define fs 48000UL

DATA left, right, out;

Int32 finalAvgs[6];
Int32 finalCorrections[6];
Int32 finalLog[6];
Int32 myAvg[512];
Int16 mypFFT[16384];
Int16 sweepResult[16384];
Int32 temp;
DATA AMP;
Uint32 eqON;
void Reset();

Int16 output;
Int16 biq[2 * 6 * NUM_FILTERS];
Int16 myBuff[2 * 4 * NUM_FILTERS];
Int32 scale[NUM_FILTERS];

interrupt void I2S_ISR()
{
	volatile int i, j;
	Int16 x[1], temp, temp2;
	Int16  left = 0;

	AIC_read2(x,&left);
	AIC_write2(output,output);

	output = 0;
	for(i=0; i<6; ++i) //NUM_FILTERS
	{
		temp = (((Int32)(IIR_DF1(left, &biq[2*i*BIQ_COEFF], &myBuff[2*i*4]))));
		temp2 = (((Int32)(IIR_DF1(temp, &biq[(2*i + 1)*BIQ_COEFF], &myBuff[(2*i + 1)*4])))*adjust[i]) >> 14;
		if(eqON)
		{
			output += (((Int32)temp2) * finalCorrections[i]) >> 15;
		}
		else
		{
			output += temp2 >> 1;
		}
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

//Int16 sweepResult[16384];

// -14 dB
#define MINVAL 3269

void main(void)
{
	unsigned int start_switch = 1;
	volatile Uint16 i,j;
	Uint32 myMin;
    volatile Uint16 key;

   	_disable_interrupts();

	// Initialize Filters
   	for(i=0; i<NUM_FILTERS; ++i)
   	{
   		redefineFilter((Uint16)i, &biq[2*i*BIQ_COEFF]);
   	}

   	// Initalize final corrections to pass-through
	for(i=0; i<6; ++i)
	{
		finalCorrections[i]=16384;
	}

	// System initialization
  	USBSTK5515_init();
  	AIC_init();
    Init_SAR();
  	I2S_interrupt_setup();
  	InitSpi();
  	My_LED_init();
	XVGAinit(start_switch);
	start_switch = 0;
	XVGAinit(start_switch);


	while(1)
	{
		toggle_LED(0);	toggle_LED(1);
		// Init: wait for user input to start sweep
		while(1)
		{
			key = Get_Key_Human();
			if(key == SW1 || key == SW2)
			{
				for(i=65535; i; --i)
				{
					asm("	nop");
				}
				break;
			}
		}

		toggle_LED(0);
		eqON = 0;

		recordSweep(40, 20000, fs, sweepResult, myAvg);

		averageFFT512to6(myAvg, finalAvgs, &myMin);

		for(i=0; i<6; ++i)
		{
			finalCorrections[i] = (myMin<<14)/finalAvgs[i]; // Q14 - division factor
			if(finalCorrections[i] < MINVAL)
			{
				finalCorrections[i] = MINVAL;
			}
		}


		GoTo(FFT_DRAW_OFFSET,0);
		for(i=0; i<NUMAVGBINS; ++i)
		{
			Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i], (Int16)(finalCorrections[i] >> 6));
			Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], (Int16)(finalCorrections[i] >> 6));
			Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], 0);
		}
		XVGAinit(start_switch);

		// Wait to continue
		while(1)
		{
			key = Get_Key_Human();
			if(key == SW1 || key == SW2)
			{
				for(i=65535; i; --i)
				{
					asm("	nop");
				}
				break;
			}
		}
		toggle_LED(1);
		toggle_LED(0);
		eqON = 1 - eqON;

		_enable_interrupts();
		while(1)
		{

			_disable_interrupts();
			key = Get_Key_Human();
			_enable_interrupts();
			if(key == SW1)
			{
				toggle_LED(0);
				eqON = 1 - eqON;
				for(j=65535; j; --j)
				{
					for(i = 4; i; i--)
					{
					asm("	nop");
					}
				}
			}
			else if(key == SW2)
			{
				_disable_interrupts();
				if(eqON)
				{
					toggle_LED(0);
					eqON = 1 - eqON;
				}
				for(i=65535; i; --i)
				{
					asm("	nop");
				}
				break;
			}
		}
	}

}

#include <stdlib.h>
#include <usbstk5515.h>

#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include "cheby100N512.h"
#include <Dsplib.h>

//#include "tunable_filter.h"

#define FOREVER 1
#define BLUE 2

#define PI 3.14159265

void XVGAinit(Uint16);
void GoTo(Uint16 x, Uint16 y);
void Draw(Uint16 color, Uint16 x, Uint16 y);
void InitSpi(void);
void InitSystem(void);
void ConfigPort(void);


#define BUFSIZE 512

///////////////////////////////////Uint16 VolumeCheck;
Uint32 Counter;

DATA bOne	[2*BUFSIZE];//Buffer 1
DATA bTwo 	[2*BUFSIZE];//Buffer 2
DATA bOut	[2*BUFSIZE];//Buffer 3--FFT output goes here.


DATA *pAIC, *pFFT, *pDONE;//Pointers to Current buffers
DATA AMP;
void Reset();



long FFracSqrt(long x)
{
	/* The definitions below yield 2 integer bits, 30 fractional bits */
	#define FRACBITS 30    /* Must be even! */
	#define ITERS    (15 + (FRACBITS >> 1))

    unsigned long root, remHi, remLo, testDiv, count;
    root = 0;         /* Clear root */
    remHi = 0;        /* Clear high part of partial remainder */
    remLo = x;        /* Get argument into low part of partial remainder */
    count = ITERS;    /* Load loop counter */
    do {
        remHi = (remHi << 2) | (remLo >> 30); remLo <<= 2;  /* get 2 bits of arg */
        root <<= 1;   /* Get ready for the next bit in the root */
        testDiv = (root << 1) + 1;    /* Test radical */
        if (remHi >= testDiv) {
            remHi -= testDiv;
            root += 1;
        }
    } while (count-- != 0);
return(root);
}


interrupt void I2S_ISR()
{
	Int16 x[1];
	Int16  left, output;
	AIC_read2(x,&left);
	output = left;
	AIC_write2(output,output);


	if(Counter < (BUFSIZE*2))
	{
		pAIC[Counter] = output;  //Only use evens for FFT function
		pAIC[Counter+1] = 0;	//No imaginary part
		Counter += 2;
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


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void main(void)
{

    Uint16 start_switch;
    Int32 tmp,tmp2,  b;

    //My variables
    Uint16 rotate;
	Uint16 BinValues[5];
	BinValues[0] = 2;   // Filter 1, 1   through 3   bins
	BinValues[1] = 6;   // Filter 2, 4   through 7   bins
	BinValues[2] = 16;  // Filter 3, 8   through 17  bins
	BinValues[3] = 41;  // Filter 4, 18  through 42  bins
	BinValues[4] = 103; // Filter 5, 43  through 104 bins
	BinValues[5] = 255; // Filter 6, 105 through 256 bins

	Uint16 Bin1Samples[2], Bin2Samples[2], Bin3Samples[2], Bin4Samples[2], Bin5Samples[2], Bin6Samples[2] = {{0}};
	Uint32 Averages[5] = {{0}};
	Uint16 SweepNumber;
	SweepNumber = 1; //Need to actually loop through this
	//End of my variables

   	DATA *temp1;
    pAIC = &bOne[0];
   	pFFT = &bTwo[0];
   	pDONE = &bOut[0];
   	Counter = AMP = 0;
   	Int32 BUFCHK;
   	volatile Int16 Reg[BUFSIZE/2] = {{1}};

   	_disable_interrupts();
    InitSystem();
    ConfigPort();
   	USBSTK5515_init();
   	AIC_init();
   	I2S_interrupt_setup();
    InitSpi();
	_enable_interrupts();
    // initialize SPI


	start_switch = 1;


	while(FOREVER) {

		if(Counter >= (BUFSIZE*2))
		{
			//Rotate buffers
			temp1= pFFT;
			pFFT = pAIC;
			pAIC = temp1;

			//Do cfft with scaling.
			for (b=0; b < 512; b = b+1)
			{
				pFFT[b] = ((Int32)pFFT[b]*(Int32)chebwin512[b]) >>15;
			}

			cfft_SCALE(pFFT, BUFSIZE);
			cbrev(pFFT, pDONE, BUFSIZE);

			XVGAinit(start_switch);   // switch display page

			GoTo(100,0);
			start_switch = 0;
			for (BUFCHK = 0; BUFCHK < BUFSIZE; BUFCHK = BUFCHK + 2)
			{
				tmp = ((Int32)pDONE[BUFCHK]*pDONE[BUFCHK]) + ((Int32)pDONE[BUFCHK+1] * pDONE[BUFCHK+1]);
				tmp2 = FFracSqrt(tmp);
				tmp2 = tmp2 >> 14;  // Should really be >>15.  Done for larger dynamic
				// range.  But now we need to check for overflow.
				AMP = tmp2>32767?32767:tmp2<-32768?-32768:tmp2; // amplitude of the output sine wave
				Reg[BUFCHK >> 1] = AMP;
				Draw(BLUE,100+BUFCHK/2, AMP >> 4 );
			}
			Counter = 0;

			//My code
			for (rotate = 0; rotate <  256; rotate++)
			{
				if (rotate <= BinValues[0])
				{
					Bin1Samples[SweepNumber] += Reg[rotate];
				}
				else if (rotate > BinValues[0] && rotate <= BinValues[1])
				{
					Bin2Samples[SweepNumber] += Reg[rotate];
				}
				else if (rotate > BinValues[1] && rotate <= BinValues[2])
				{
					Bin3Samples[SweepNumber] += Reg[rotate];
				}
				else if (rotate > BinValues[2] && rotate <= BinValues[3])
				{
					Bin4Samples[SweepNumber] += Reg[rotate];
				}
				else if (rotate > BinValues[4] && rotate <= BinValues[5])
				{
					Bin5Samples[SweepNumber] += Reg[rotate];
				}
				else
				{
					Bin6Samples[SweepNumber] +=Reg[rotate];
				}
			}

			Bin1Samples[SweepNumber] = Bin1Samples[SweepNumber] / (BinValues[0] + 1); 			 //Average Bin 1
			Bin2Samples[SweepNumber] = Bin2Samples[SweepNumber] / (BinValues[1] - BinValues[0]); //Average Bin 2
			Bin3Samples[SweepNumber] = Bin3Samples[SweepNumber] / (BinValues[2] - BinValues[1]); //Average Bin 3
			Bin3Samples[SweepNumber] = Bin4Samples[SweepNumber] / (BinValues[3] - BinValues[2]); //Average Bin 4
			Bin3Samples[SweepNumber] = Bin5Samples[SweepNumber] / (BinValues[4] - BinValues[3]); //Average Bin 5
			Bin3Samples[SweepNumber] = Bin6Samples[SweepNumber] / (BinValues[5] - BinValues[4]); //Average Bin 6

			//once looped through 3 times
			for (rotate = 0; rotate <=2; rotate++)
			{
				Averages[0] += Bin1Samples[rotate];
				Averages[1] += Bin2Samples[rotate];
				Averages[2] += Bin3Samples[rotate];
				Averages[3] += Bin4Samples[rotate];
				Averages[4] += Bin5Samples[rotate];
				Averages[5] += Bin6Samples[rotate];
			}

			Averages[0] = Averages[0]/3; // Assuming 3 sweeps
			Averages[1] = Averages[1]/3; // Assuming 3 sweeps
			Averages[2] = Averages[2]/3; // Assuming 3 sweeps
			Averages[3] = Averages[3]/3; // Assuming 3 sweeps
			Averages[4] = Averages[4]/3; // Assuming 3 sweeps
			Averages[5] = Averages[5]/3; // Assuming 3 sweeps
			// end of my code

		}

	}

	TERMINATE:
	printf("Not enough time to compute FFT\n");

}

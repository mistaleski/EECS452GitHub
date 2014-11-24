/*
 * FFT.c
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#include "FFT.h"

Uint16 fftCounter;

DATA *pAIC, *pFFT, *pDONE;//Pointers to Current buffers

void initFFT(DATA *_pAIC, DATA *_pFFT, DATA *_pDONE)
{
    pAIC = &_pAIC[0];
   	pFFT = &_pFFT[0];
   	pDONE = &_pDONE[0];
   	fftCounter = 0;
}

Uint8 processFFT()
{
	DATA *temp1;
	Uint16 b;

	if(!FFTready())
	{
		return 1;
	}
	else
	{
		//Rotate buffers
		temp1= pFFT;
		pFFT = pAIC;
		pAIC = temp1;

		// apply Chebyshvev filter
		for (b=0; b < 512; b = b+1)
		{
			pFFT[b] = ((Int32)pFFT[b]*(Int32)chebwin512[b]) >>15;
		}

		//Do cfft with scaling.
		cfft_SCALE(pFFT, FFTSIZE);
		cbrev(pFFT, pDONE, FFTSIZE);
	}
	return 0;
}

Uint8 FFTready()
{
	if(fftCounter >= FFTSIZE*2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void showFFT(Int32 *maxIndex, Int32 *max)
{
	DATA AMP;
	Int32 tmp,tmp2;
	Uint16 n;

    *max = 0;
	*maxIndex = 512;

	//Find magnitude of X(n/2).
	GoTo(100,0);
	for (n = 0; n < FFTSIZE; n = n + 2)
	{
		tmp = ((Int32)pDONE[n]*pDONE[n]) + ((Int32)pDONE[n+1] * pDONE[n+1]);
		tmp2 = FFracSqrt(tmp);
		tmp2 = tmp2 >> 14;  // Should really be >>15.  Done for larger dynamic
						 // range.  But now we need to check for overflow.
		AMP = tmp2>32767?32767:tmp2<-32768?-32768:tmp2; // amplitude of the output sine wave
		// Reg[n >> 1] = AMP;
		Draw(BLUE,100+n/2, AMP >> 4 );

		if(AMP > *max)
		{
			*max = AMP;
			*maxIndex = n >> 1;
		}

	}

	fftCounter = 0;

}


Uint8 queueFFT(Int16 x)
{
	if(fftCounter < (FFTSIZE*2))
	{
		pAIC[fftCounter] = x;  //Only use evens for FFT function
		pAIC[fftCounter+1] = 0;	//No imaginary part
		fftCounter += 2;
		return 0;
	}
	return 1;
}

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

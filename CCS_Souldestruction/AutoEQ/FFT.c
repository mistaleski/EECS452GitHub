/*
 * FFT.c
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#include "FFT.h"


Uint8 processFFT(DATA *pFFT, DATA *pDONE, Uint32 *avgs)
{
	Uint16 b, i;
	DATA AMP;
	Int32 tmp,tmp2;
	Uint16 n;

	for(i=0; i<FFTSIZE; ++i)
	{
		avgs[i] = 0;
	}

	// Draw
	GoTo(FFT_DRAW_OFFSET,0);

	// Take 16 1024-point FFTs
	for(i = 0; i < 16; ++i)
	{
		// apply Chebyshvev filter
		for (b=0; b < 512; b = b+1)
		{
			pFFT[i*1024+b] = ((Int32)pFFT[i*1024+b]*(Int32)chebwin512[b]) >>15;
		}

		//Do cfft with scaling.
		cfft_SCALE((pFFT+(i*1024)), FFTSIZE);
		cbrev((pFFT+(i*1024)), pDONE, FFTSIZE);

#ifdef SWEEPREC_DEBUG
		XVGAinit(0);
#endif // DEBUG
		GoTo(FFT_DRAW_OFFSET,0);
		for (n = 0; n < FFTSIZE; n = n + 2)
		{
			tmp = ((Int32)pDONE[n]*pDONE[n]) + ((Int32)pDONE[n+1] * pDONE[n+1]);
			tmp2 = FFracSqrt(tmp);
			tmp2 = tmp2 >> 14;  // Should really be >>15.  Done for larger dynamic
							 // range.  But now we need to check for overflow.
			AMP = tmp2>32767?32767:tmp2<-32768?-32768:tmp2; // amplitude of the output sine wave
			avgs[n>>1] += (Int32) AMP;
#ifdef SWEEPREC_DEBUG
			Draw(BLUE,FFT_DRAW_OFFSET+(n>>1), AMP >> 4);
			Draw(BLUE,FFT_DRAW_OFFSET+((n>>1)+1), AMP >> 4);
#endif // DEBUG
		}
	}

	XVGAinit(0);
	GoTo(FFT_DRAW_OFFSET,0);
	for(i=0; i<FFTSIZE; ++i)
	{
		avgs[i] = avgs[i] >> 4;
		Draw(BLUE,FFT_DRAW_OFFSET+i, avgs[i] >> 4);
		Draw(BLUE,FFT_DRAW_OFFSET+(i+1), avgs[i] >> 4);
	}
	XVGAinit(0);

	return 0;
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

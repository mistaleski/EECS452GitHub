/*
 * avgFFT512to6.c
 *
 *  Created on: Dec 9, 2014
 *      Author: cplacy
 */

#include "avgFFT512to6.h"


void averageFFT512to6(Int32 *myFFT512, Int32 *myAvgs6)
{

	Uint16 i,j;
	Uint16 index = 0;
	Uint32 tot;

	for(i=0; i<NUMAVGBINS; ++i)
	{
		tot = 0;
		// Ignore DC term
		for(j=binsBounds[i]+1; j<=binsBounds[i+1];++j)
		{
			tot += myFFT512[j];
		}
		myAvgs6[i] = tot/(((Int32)binsBounds[i+1])-((Int32)binsBounds[i]));
	}

	XVGAinit(0);
	GoTo(FFT_DRAW_OFFSET,0);
	for(i=0; i<NUMAVGBINS; ++i)
	{
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i], (Int16)(myAvgs6[i] >> 4));
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], (Int16)(myAvgs6[i] >> 4));
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], 0);
	}
	XVGAinit(0);

}


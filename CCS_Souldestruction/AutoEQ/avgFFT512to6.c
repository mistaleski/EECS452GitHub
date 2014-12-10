/*
 * avgFFT512to6.c
 *
 *  Created on: Dec 9, 2014
 *      Author: cplacy
 */

#include "avgFFT512to6.h"


void averageFFT512to6(Int32 *myFFT512, Int32 *myAvgs6, Uint32 *min)
{

	Uint16 i,j;
	Uint32 tot;
	Uint32 total, minF, maxF,avg;

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
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i], (Int16)(myAvgs6[i] >> 3));
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], (Int16)(myAvgs6[i] >> 3));
		Draw(BLUE,FFT_DRAW_OFFSET+binsBounds[i+1], 0);
	}

	total = 0;
	maxF = 0;
	minF = 4294967290;


	for(j=0; j<6; ++j)
	{
		//total += myAvgs6[j];			// calculate the total summation of all filters
		if (myAvgs6[j] > maxF)
		{
			maxF = myAvgs6[j];		// find the maximum bin
		}
		if (myAvgs6[j] < minF)
		{
			minF = myAvgs6[j];		// find the minimum bin
		}
	}
	//avg = total/((Int32)6);				// calculate the average of all bins

//	GoTo(10, (Int16)(avg >> 3));		// plot AVG bin line
//	Draw(BLUE,629, (Int16)(avg >> 3));
//	GoTo(10, (Int16)(maxF >> 3));		// plot MAX bin line
//	Draw(BLUE,629, (maxF >> 3));
//	GoTo(10, (Int16)(minF >> 3));		// plot MIN bin line
//	Draw(BLUE,629, (minF >> 3));

	*min = minF;

	XVGAinit(0);

}


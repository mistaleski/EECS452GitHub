/*
 * AdaptiveNotch.c
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#include "AdaptiveNotch.h"

Uint32 filterCenter[NUM_CANCELERS];
Int16 biq[6*NUM_CANCELERS];
Int16 cancelBuffs[4*NUM_CANCELERS];
Uint8 next_buff;

Int32 didRepeat,fftBin;

void stepNotch(Int32 max, Int32 maxIndex)
{

	if (max>_FEEDBACK_THRESHOLD && didRepeat == 0)
	{
		fftBin = maxIndex;
		didRepeat++;
	}
	else if (max>_FEEDBACK_THRESHOLD &&
			didRepeat &&
				(fftBin < maxIndex + _FEEDBACK_FREQUENCY_TOLERANCE ||
				 fftBin > maxIndex - _FEEDBACK_FREQUENCY_TOLERANCE
				)
			)
	{
		didRepeat++;
	}
	else
	{
		didRepeat = 0;
	}
	if (didRepeat > _MAXFREQ_REPEATS_THRESHOLD && fftBin > _MIN_NOTCH_FREQ)
	{
		filterCenter[next_buff] = fftBin;
		didRepeat = 0;
		redefineFilter(filterCenter[next_buff], &biq[next_buff*NUM_CANCELERS]);
		next_buff++;
		if(next_buff >= NUM_CANCELERS)
		{
			next_buff = 0;
		}
	}

}


void applyNotches(Int16 *in)
{
	Uint8 i;

	for(i = 0; i < NUM_CANCELERS; i++)
	{
		*in = IIR_DF1(*in, &biq[NUM_CANCELERS*i], &cancelBuffs[4*i]);
	}

}


void initNotches()
{
	Uint8 i;

	// Set filters to pass-throughs, clear internal state
	for(i =0; i<NUM_CANCELERS; i++)
	{
		initFilter(&biq[NUM_CANCELERS*i]);
		filterCenter[i] = 512;
		cancelBuffs[4*i + 0] = 0;
		cancelBuffs[4*i + 1] = 0;
		cancelBuffs[4*i + 2] = 0;
		cancelBuffs[4*i + 3] = 0;
	}

	next_buff = 0;
    didRepeat = 0;
    fftBin = 0;
}

void drawThreshold()
{
	GoTo(100,_FEEDBACK_THRESHOLD >>4);
	Draw(BLUE,100+512, _FEEDBACK_THRESHOLD >>4);
}

void drawNotches()
{
	Uint8 i;

	for(i=0; i< NUM_CANCELERS; i++)
	{
		if(filterCenter[i] != 512)
		{
			GoTo(filterCenter[i]-_NOTCH_LINE_SIZE+100,(_FEEDBACK_THRESHOLD >>4)-_FEEDBACK_FREQUENCY_TOLERANCE);
			Draw(BLUE,filterCenter[i]+_NOTCH_LINE_SIZE+100, (_FEEDBACK_THRESHOLD >>4)-_FEEDBACK_FREQUENCY_TOLERANCE);
		}
	}
}

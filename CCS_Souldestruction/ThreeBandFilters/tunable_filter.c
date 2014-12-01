/*
 * tunable_filter.c
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#include "tunable_filter.h"


void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq)
{
	_biq[0] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 0] >> 1;		//b0
	_biq[1] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 1] >> 1;		//b1
	_biq[2] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 2] >> 1;		//b2

	_biq[3] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 3] >> 1;		//a0  -- this one is actually ignored.
	_biq[4] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 4] >> 1;		//a1
	_biq[5] =  ThreeBandfilters[FILTER_SELECT*BIQ_COEFF + 5] >> 1;		//a2
}

#define B0 ((Int32)_biq[0])
#define B1 ((Int32)_biq[1])
#define B2 ((Int32)_biq[2])
#define A0 ((Int32)_biq[3])
#define A1 ((Int32)_biq[4])
#define A2 ((Int32)_biq[5])

Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff) {
	Int16 y;
	Int32 Acc;

		Acc = ((Int32)input) * B0 + ((Int32)(delay_buff[0])) * B1 + \
				((Int32)(delay_buff[1])) * B2 - ((Int32)(delay_buff[2])) * A1 - \
				((Int32)(delay_buff[3])) * A2;
				// takes the 16-bit Q15 values from the input
				// and Z-1 blocks and multiply them by the 16-bit Q13 coeffs
				// to get a 32-bit Q28.

		Int32 temp42 = Acc >> 14;
		Acc = temp42 > 32767 ? 32767 : temp42 < -32768 ? -32768 : temp42; // Converts to a 16-bit Q15 with rounding and saturation.

		//updates the various delay blocks
		delay_buff[1]	=  delay_buff[0];
		delay_buff[0]	=  input;
		delay_buff[3]	= delay_buff[2];
		delay_buff[2]	= (Int16)Acc;

		y = (Int16)Acc;

	return y;
}

void initFilter(Int16 *_biq)
{
	/// set gain to 1 >> pass-through
	_biq[0] =  16384;		//b0
	_biq[1] =  0;		//b1
	_biq[2] =  0;		//b2

	_biq[3] =  16384;		//a0  -- this one is actually ignored.
	_biq[4] =  0;		//a1
	_biq[5] =  0;		//a2
}

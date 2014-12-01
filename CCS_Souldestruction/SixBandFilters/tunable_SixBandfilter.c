/*
 * tunable_filter.c
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#include "tunable_SixBandfilter.h"

#define B01 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  0] >> 1
#define B11 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  1] >> 1
#define B21 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  2] >> 1
#define A01 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  3] >> 1
#define A11 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  4] >> 1
#define A21 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  5] >> 1
#define B02 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  6] >> 1
#define B12 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  7] >> 1
#define B22 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  8] >> 1
#define A02 SixBandfilters[FILTER_SELECT*BIQ_COEFF +  9] >> 1
#define A12 SixBandfilters[FILTER_SELECT*BIQ_COEFF + 10] >> 1
#define A22 SixBandfilters[FILTER_SELECT*BIQ_COEFF + 11] >> 1

void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq)
{
	_biq[0] = A11;
	_biq[1] = B11;
	_biq[2] = A21;
	_biq[3] = B21;
	_biq[4] = B01;
	_biq[5] = A12;
	_biq[6] = B12;
	_biq[7] = A22;
	_biq[8] = B22;
	_biq[9] = B02;
}

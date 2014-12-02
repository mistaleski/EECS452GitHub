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

void redefineFilter(Uint16 FILTER_SELECT, Uint16 *_biq)
{
	/*
	_biq[0] = (Int16)(B01);
	_biq[1] = (Int16)(B11);
	_biq[2] = (Int16)(B21);
	_biq[3] = (Int16)(A11);
	_biq[4] = (Int16)(A21);
	*/

	_biq[0] = 4;
	_biq[1] = 8;
	_biq[2] = 4;
	_biq[3] = 16384;
	_biq[4] = -32341;
	_biq[5] = 15973;

}

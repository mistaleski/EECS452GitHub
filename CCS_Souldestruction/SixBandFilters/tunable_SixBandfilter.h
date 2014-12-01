/*
 * tunable_ThreeBandfilter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#ifndef TUNABLE_SIXBANDFILTER_H_
#define TUNABLE_SIXBANDFILTER_H_

#include <usbstk5515.h>
#include "SixBandfilters.h"


#define NUM_FILTERS 6
#define NUM_BIQUADS NUM_FILTERS*2
#define BIQ_COEFF 5

static const Int32 adjust[NUM_FILTERS] = {
	32768,
	73800,
	73873,
	74332,
	76306,
	101726
};




Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);


#endif /* TUNABLE_SIXBANDFILTER_H_ */

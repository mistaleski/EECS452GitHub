#ifndef _TUNABLE_SIXBANDFILTER_H
#define _TUNABLE_SIXBANDFILTER_H

/*
 * tunable_ThreeBandfilter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#include <usbstk5515.h>
#include "SixBandfilters.h"


#define NUM_FILTERS 6
#define NUM_BIQUADS NUM_FILTERS*2
#define BIQ_COEFF 6

static const Int32 adjust[NUM_FILTERS] = {
		23170, 38903, 44891, 49449, 56514, 70092
};



void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);

Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);


#endif /* TUNABLE_SIXBANDFILTER_H_ */

/*
 * tunable_ThreeBandfilter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#ifndef TUNABLE_SIXBANDFILTER_H_
#define TUNABLE_SIXBANDFILTER_H_

#include <usbstk5515.h>
#include "tunable_SixBandfilter.h"


#define BIQ_COEFF 6

#define ADJUST_BAND_1  32768 //multiply by band
#define ADJUST_BAND_2  73800
#define ADJUST_BAND_3  73873
#define ADJUST_BAND_4  74332
#define ADJUST_BAND_5  76306
#define ADJUST_BAND_6  101726


Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);


#endif /* TUNABLE_SIXBANDFILTER_H_ */

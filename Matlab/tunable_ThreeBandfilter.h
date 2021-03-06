/*
 * tunable_ThreeBandfilter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#ifndef TUNABLE_THREEBANDFILTER_H_
#define TUNABLE_THREEBANDFILTER_H_

#include <usbstk5515.h>
#include "tunable_ThreeBandfilter.h"


#define BIQ_COEFF 6

#define ADJUST_BAND_1  99 //multiply by band
#define ADJUST_BAND_2  684
#define ADJUST_BAND_3  6683
#define ADJUST_BAND_4  7374
#define ADJUST_BAND_5  12655


Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);


#endif /* TUNABLE_THREEBANDFILTER_H_ */

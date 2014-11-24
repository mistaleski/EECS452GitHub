/*
 * tunable_EQfilter.h
 *
 *  Created on: Nov 23, 2014
 *      Author: mrmista
 */
 
#ifndef TUNABLE_EQFILTER_H_
#define TUNABLE_EQFILTER_H_

#include <usbstk5515.h>
#include "tunable_EQfilter.h"


#define BIQ_COEFF 6

#define ADJUST_BAND_1 = 123 //multiply by band
#define ADJUST_BAND_2 = 249
#define ADJUST_BAND_3 = 663
#define ADJUST_BAND_4 = 1664
#define ADJUST_BAND_5 = 3934
#define ADJUST_BAND_6 = 8241
#define ADJUST_BAND_7 = 12925


Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);


#endif /* TUNABLE_EQFILTER_H_ */
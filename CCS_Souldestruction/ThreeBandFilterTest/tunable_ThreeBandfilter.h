/*
 * tunable_ThreeBandfilter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#ifndef TUNABLE_THREEBANDFILTER_H_
#define TUNABLE_THREEBANDFILTER_H_

#include <usbstk5515.h>
#include "ThreeBandfilters.h"


#define BIQ_COEFF 6

Int16 IIR_DF1_2(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter2(Uint16 FILTER_SELECT, Int16 *_biq);


#endif /* TUNABLE_THREEBANDFILTER_H_ */

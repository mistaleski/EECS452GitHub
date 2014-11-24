/*
 * tunable_filter.h
 *
 *  Created on: Nov 15, 2014
 *      Author: cplacy
 */

#ifndef TUNABLE_FILTER_H_
#define TUNABLE_FILTER_H_

#include <usbstk5515.h>
#include "notchFilterCoefs.h"

#define BIQ_COEFF 6

Int16 IIR_DF1(Int16 input, Int16 *_biq, Int16 *delay_buff);
void redefineFilter(Uint16 FILTER_SELECT, Int16 *_biq);
void initFilter(Int16 *_biq);


#endif /* TUNABLE_FILTER_H_ */

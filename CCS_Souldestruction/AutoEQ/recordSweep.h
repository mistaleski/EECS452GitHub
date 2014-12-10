/*
 * recordSweep.h
 *
 *  Created on: Dec 4, 2014
 *      Author: Lacy
 */

#ifndef RECORDSWEEP_H_
#define RECORDSWEEP_H_

#include <usbstk5515.h>
#include <AIC_func.h>
#include "sineTable.h"
#include "FFT.h"

static DATA mypOUT[1024];//Pointers to Current buffers

void recordSweep(Uint32 _min_freq, Uint32 _max_freq, Uint32 fs, Int16 *in, Int32 *avg);



#endif /* RECORDSWEEP_H_ */

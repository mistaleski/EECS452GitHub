/*
 * avgFFT512to6.h
 *
 *  Created on: Dec 9, 2014
 *      Author: cplacy
 */

#ifndef AVGFFT512TO8_H_
#define AVGFFT512TO8_H_

#include <usbstk5515.h>
#include "XVGA.h"
#include "FFT.h"

#define NUMAVGBINS 6

	static const Uint16 binsBounds[NUMAVGBINS+1] =
	{
	0,
	2,
	6,
	16,
	41,
	103,
	255
	};

void averageFFT512to6(Int32 *myFFT512, Int32 *myAvgs6, Uint32 *min);


#endif /* AVGFFT512TO8_H_ */

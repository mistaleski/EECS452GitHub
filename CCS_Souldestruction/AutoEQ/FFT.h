/*
 * FFT.h
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#ifndef FFT_H_
#define FFT_H_

#define FFT_DRAW_OFFSET 63

#include <stdlib.h>
#include <usbstk5515.h>
#include <Dsplib.h>
#include "cheby100N512.h"
#include "XVGA.h"

//#define SWEEPREC_DEBUG

// Defines the size of the FFT. Must be a multiple of 2
#define FFTSIZE 512

// Rotates FFT buffers and takes the FFT if data buffer is full,
// else leaves buffers as is and returns 1
Uint8 processFFT(DATA *_pFFT, DATA *_pDONE, Uint32 *avgs);


long FFracSqrt(long x);

#endif /* FFT_H_ */

/*
 * FFT.h
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#ifndef FFT_H_
#define FFT_H_

#include <stdlib.h>
#include <usbstk5515.h>
#include <Dsplib.h>
#include "cheby100N512.h"
#include "XVGA.h"

// Defines the size of the FFT. Must be a multiple of 2
#define FFTSIZE 512

// REQ:	_pAIC, _pFFT, and _pDONE are pointers to arrays of size FFTSIZE
// EFF: Initializes the FFT buffer pointers to point to user-inputted arrays
void initFFT(DATA *_pAIC, DATA *_pFFT, DATA *_pDONE);

// Rotates FFT buffers and takes the FFT if data buffer is full,
// else leaves buffers as is and returns 1
Uint8 processFFT();

Uint8 FFTready();

/// Writes FFT to display.
/// @param max is set to the maximum value of the FFT
/// @param maxIndex is set to the index of max
void showFFT(Int32 *maxIndex, Int32 *max);


Uint8 queueFFT(Int16 x);

long FFracSqrt(long x);

#endif /* FFT_H_ */

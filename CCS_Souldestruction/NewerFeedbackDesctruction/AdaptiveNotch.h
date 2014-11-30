/*
 * AdaptiveNotch.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Charlie Lacy
 */

#ifndef ADAPTIVENOTCH_H_
#define ADAPTIVENOTCH_H_

#include <stdlib.h>
#include <usbstk5515.h>
#include "tunable_filter.h"
#include "XVGA.h"

#define NUM_CANCELERS 3
//
#define _MIN_NOTCH_FREQ 39
#define _FEEDBACK_THRESHOLD 4000
#define _FEEDBACK_FREQUENCY_TOLERANCE 5
#define _MAXFREQ_REPEATS_THRESHOLD 5
#define _NOTCH_LINE_SIZE 5

/**
 * Performs the next step of the adaptive notch filter calculation
 * based on the last FFT result.
 *
 * This function updates the internal state, specifically the
 * desired center frequencies of the notch filters. It does this
 * by keeping track of the maximum value of the FFT and checking if
 * if is greater than _FEEDBACK_THRESHOLD. Once a frequency crosses this
 * threshold, if the max frequency remains within _FEEDBACK_FREQUENCY_TOLERANCE
 * bins of the initial high bin for _MAXFREQ_REPEATS_THRESHOLD FFT plottings,
 * then one of filters in the notch bank will be assigned to cancel
 * the frequency corresponding to the initial high bin.
 *
 * @param max is the last calculated maximum value of the FFT
 * @param maxIndex is the index of the last calculated maximum value of the FFT
 */
void stepNotch(Int32 max, Int32 maxIndex);

/**
 * Applies notch filters to an input
 * @param *in points to the next sample of audio input (one value)
 * @return Returns the output of the notch filter bank
 */
void applyNotches(Int16 *in);

/**
 * Initializes notch filters and sets their centers to a sentinel value, indicating disable
 */
void initNotches();

/**
 * Draws the threshold value on the VGA display
 */
void drawThreshold();

/**
 * Draws the location of the notch filters on the VGA display
 */
void drawNotches();

#endif /* ADAPTIVENOTCH_H_ */

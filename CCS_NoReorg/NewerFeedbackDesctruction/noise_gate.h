/*
 * noise_gate.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Rossen Pomakov
 */

#ifndef NOISE_GATE_H_
#define NOISE_GATE_H_

#define STATE_IDLE      0
#define STATE_ATTACK 	1
#define STATE_ACTIVE    2
#define STATE_DECAY  	3

#define SF 48

#define ATTACK_TIME_DEFAULT 1		// attack tim in ms (must not exceed 500 ms)
#define DECAY_TIME_DEFAULT 	2		// release time in ms (must not exceed 500 ms)
#define HOLD_TIME_DEFAULT 	100	// hold time in ms
#define THRESHOLD_DEFAULT 	2000	// threshold value (out of


// input:  			Real Time Audio Signal
// threshold:		Signal level required to open gate
// attack_time_ms:  Attack time in ms (must not exceed 500 ms)
// decay_time_ms:  	Decay time in ms (must not exceed 500 ms)
// hold_time_ms:	Hold time in ms
//
// RETURNS:  Output of noise gate.

// Input needs to be normalized before passing into the function.
// threshold is set outside of function
// Future Goals:
//  - add a way to average samples to find the threshold value needed
//  - apply button functionality to this threshold function; reanalysis any time
//  - what happens when the you are ramping up and the value falls below threshold?
int noise_gate(int input, int threshold, int attack_time_ms, int decay_time_ms, int hold_time_ms);

/**
 * Implements a noise gate with the default parameters
 * @param input is the next sample of input audio
 * @return the next sample of the output from the noise gate
 * @see noise_gate for full description of noise gate functionalty
 */
int noise_gate_default(int input);


#endif /* NOISE_GATE_H_ */

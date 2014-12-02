/*
 * visuals.h
 *
 *  Created on: Dec 01, 2014
 *      Author: Rossen Pomakov
 */

#ifndef VISUALS_H_
#define VISUALS_H_

int visuals(Uint8 is_gate_on, Uint8 is_feedback_on);

/**
 * Plots a box with indicators for noise gate and feedback rejection
 * @param is_gate_on indicates if the noise gate is on
 * @param is_feedback_on indicates if feedback rejection is on
 * @return nothing
 */
 
int noise_gate_default(int input);

#endif /* NOISE_GATE_H_ */

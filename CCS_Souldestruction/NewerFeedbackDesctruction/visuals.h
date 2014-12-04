/*
 * visuals.h
 *
 *  Created on: Dec 01, 2014
 *      Author: Rossen Pomakov
 */

#ifndef VISUALS_H_
#define VISUALS_H_

#include <stdlib.h>
#include <usbstk5515.h>
#include <usbstk5515_gpio.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_led.h>
#include <AIC_func.h>
#include <usbstk5515_interrupts.h>
#include <stdio.h>
#include <math.h>
#include <Dsplib.h>
#include <sar.h>

int visuals(Uint8 is_gate_on, Uint8 is_feedback_on);

/**
 * Plots a box with indicators for noise gate and feedback rejection
 * @param is_gate_on indicates if the noise gate is on
 * @param is_feedback_on indicates if feedback rejection is on
 * @return nothing
 */
 
int noise_gate_default(int input);

#endif /* NOISE_GATE_H_ */

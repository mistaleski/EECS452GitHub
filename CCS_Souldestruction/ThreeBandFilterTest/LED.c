/*
 * LED.c
 *
 *  Created on: Nov 20, 2014
 *      Author: cplacy
 */

#include "LED.h"


//Addresses of the MMIO for the GPIO out registers: 1,2
#define LED_OUT1 *((ioport volatile Uint16*)0x1C0A )
#define LED_OUT2 *((ioport volatile Uint16*)0x1C0B )
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16*)0x1C06 )
#define LED_DIR2 *((ioport volatile Uint16*)0x1C07 )

//Toggles LED specified by index Range 0 to 3
void toggle_LED(int index)
{
	if(index == 3) //Blue
		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(14));
	else if(index == 2) //Yellow(ish)
		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(15));
	else if(index == 1) //Red
		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(0));
	else if(index == 0) //Green
		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(1));
}

//Makes the GPIO associated with the LEDs the correct direction; turns them off
void My_LED_init()
{
	LED_DIR1 |= (1<<14) | (1<<15);
	LED_DIR2 |= (1<<0) | (1<<1);

	LED_OUT1 |= (1<<14) | (1<<15); //Set LEDs 0, 1 to off
	LED_OUT2 |= (1<<0) | (1<<1); //Set LEDs 2, 3 to off
}

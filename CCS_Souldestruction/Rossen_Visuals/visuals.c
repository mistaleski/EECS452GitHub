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
#include "tunable_filter.h"
#include <LCD_FCN.h>
#include <sar.h>

#define BLUE 1

int visuals(Uint8 is_gate_on, Uint8 is_feedback_on )
{

//
// is_gate_on:		Checks if gating is enabled
// is_feedback_on:  Checks if feedback rejection is enabled
//
// RETURNS:  Nothing.
/*
	Int32 th;
	th = 4000;
	Int32 tp;
	tp = (th >>4);
	GoTo(0,th >>4);					// CHANGED  --+
	Draw(BLUE,639, th >>4);			// CHANGED    +----	THRESHOLD
	GoTo(0,(th >>4)+2);				// CHANGED    +
	Draw(BLUE,639, (th >>4)+2);		// CHANGED  --+


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    	GoTo(450,tp+12);			// T
		    	Draw(BLUE,456, tp+12);
		    	GoTo(453,tp+12);
		    	Draw(BLUE,453, tp+5);
		    	GoTo(458,tp+12);			// H
		    	Draw(BLUE,458, tp+5);
		    	GoTo(458,tp+8);
		    	Draw(BLUE,462, tp+8);
		    	GoTo(462,tp+12);
		    	Draw(BLUE,462, tp+5);
		    	GoTo(465,tp+12);			// R
		    	Draw(BLUE,465, tp+5);
		    	GoTo(465,tp+12);
		    	Draw(BLUE,468, tp+12);
		    	GoTo(465,tp+8);
		    	Draw(BLUE,468, tp+8);
		    	GoTo(469,tp+11);
		    	Draw(BLUE,469, tp+9);
		    	GoTo(469,tp+7);
		    	Draw(BLUE,469, tp+5);
		    	GoTo(472,tp+12);			// E
		    	Draw(BLUE,472, tp+5);
		    	GoTo(472,tp+12);
		    	Draw(BLUE,476, tp+12);
		    	GoTo(472,tp+8);
		    	Draw(BLUE,476, tp+8);
		    	GoTo(472,tp+5);
		    	Draw(BLUE,476, tp+5);
		    	GoTo(479,tp+11);			// S
		    	Draw(BLUE,479, tp+10);
		    	GoTo(484,tp+8);
		    	Draw(BLUE,484, tp+6);
		    	GoTo(480,tp+9);
		    	Draw(BLUE,483, tp+9);
		    	GoTo(480,tp+12);
		    	Draw(BLUE,483, tp+12);
		    	GoTo(479,tp+5);
		    	Draw(BLUE,483, tp+5);
		    	GoTo(487,tp+12);			// H
		    	Draw(BLUE,487, tp+5);
		    	GoTo(487,tp+8);
		    	Draw(BLUE,491, tp+8);
		    	GoTo(491,tp+12);
		    	Draw(BLUE,491, tp+5);
		    	GoTo(494,tp+11);			// O
		    	Draw(BLUE,494, tp+6);
		    	GoTo(499,tp+11);
		    	Draw(BLUE,499, tp+6);
		    	GoTo(495,tp+12);
		    	Draw(BLUE,498, tp+12);
		    	GoTo(495,tp+5);
		    	Draw(BLUE,498, tp+5);
		    	GoTo(502,tp+12);			// L
		    	Draw(BLUE,502, tp+5);
		    	GoTo(502,tp+5);
		    	Draw(BLUE,506, tp+5);
		    	GoTo(509,tp+12);			// D
		    	Draw(BLUE,509, tp+5);
		    	GoTo(509,tp+12);
		    	Draw(BLUE,512, tp+12);
		    	GoTo(509,tp+5);
		    	Draw(BLUE,512, tp+5);
		    	GoTo(514,tp+11);
		    	Draw(BLUE,513, tp+6);		// END OF THRESOLD */

		    	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    	GoTo(400,305);				// INDICATOR BORDER
		    	Draw(BLUE,564, 305);
		    	GoTo(564,305);
		    	Draw(BLUE,564, 415);
		    	GoTo(400,305);
		    	Draw(BLUE,400, 415);
		    	GoTo(400,415);
		    	Draw(BLUE,564, 415);

		    	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    	GoTo(425,389);				// START OF NOISE GATE INDICATOR (G)
		    	Draw(BLUE,425, 376);
		    	GoTo(426,390);
		    	Draw(BLUE,430, 390);
		    	GoTo(426,375);
		    	Draw(BLUE,431, 375);
		    	GoTo(431,389);
		    	Draw(BLUE,431,389);
		    	GoTo(431,375);
		    	Draw(BLUE,431,381);
		    	GoTo(431,381);
		    	Draw(BLUE,428,381);
		    	GoTo(435,330+45);			// A
		    	Draw(BLUE,438, 345+45);
		    	GoTo(439, 345+45);
		    	Draw(BLUE,442, 330+45);
		    	GoTo(437,337+45);
		    	Draw(BLUE,440, 337+45);
		    	GoTo(438, 345+45);
		    	Draw(BLUE,439, 345+45);
		    	GoTo(445,390);				// T
		    	Draw(BLUE,453, 390);
		    	GoTo(449, 390);
		    	Draw(BLUE,449, 375);
		    	GoTo(456,345+45);			// E
		    	Draw(BLUE,456, 330+45);
		    	GoTo(456,345+45);
		    	Draw(BLUE,462, 345+45);
		    	GoTo(456,337+45);
		    	Draw(BLUE,462, 337+45);
		    	GoTo(456,330+45);
		    	Draw(BLUE,462, 330+45);		// END OF NOISE GATE INDICATOR


		    	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    	GoTo(415,345);				// START OF THE FEEDBACK INDIATOR (F)
		    	Draw(BLUE,415, 330);
		    	GoTo(415,345);
		    	Draw(BLUE,422, 345);
		    	GoTo(415,337);
		    	Draw(BLUE,420, 337);
		    	GoTo(425,345);				// E
		    	Draw(BLUE,425, 330);
		    	GoTo(425,345);
		    	Draw(BLUE,431, 345);
		    	GoTo(425,337);
		    	Draw(BLUE,431, 337);
		    	GoTo(425,330);
		    	Draw(BLUE,431, 330);
		    	GoTo(435,345);				// E
		    	Draw(BLUE,435, 330);
		    	GoTo(435,345);
		    	Draw(BLUE,441, 345);
		    	GoTo(435,337);
		    	Draw(BLUE,441, 337);
		    	GoTo(435,330);
		    	Draw(BLUE,441, 330);
		    	GoTo(445,345);				// D
		    	Draw(BLUE,445, 330);
		    	GoTo(445,345);
		    	Draw(BLUE,450, 345);
		    	GoTo(445,330);
		    	Draw(BLUE,450, 330);
		    	GoTo(451,344);
		    	Draw(BLUE,451, 331);
		    	GoTo(455,345);				// B
		    	Draw(BLUE,455, 330);
		    	GoTo(455,345);
		    	Draw(BLUE,460, 345);
		    	GoTo(455,338);
		    	Draw(BLUE,460, 338);
		    	GoTo(455,330);
		    	Draw(BLUE,460, 330);
		    	GoTo(461,344);
		    	Draw(BLUE,461, 339);
		    	GoTo(461,337);
		    	Draw(BLUE,461, 331);
		    	GoTo(465,330);				// A
		    	Draw(BLUE,468, 345);
		    	GoTo(469, 345);
		    	Draw(BLUE,472, 330);
		    	GoTo(467,337);
		    	Draw(BLUE,470, 337);
		    	GoTo(468, 345);
		    	Draw(BLUE,469, 345);
		    	GoTo(476, 344);				// C
		    	Draw(BLUE,476, 331);
		    	GoTo(477, 345);
		    	Draw(BLUE,481, 345);
		    	GoTo(477, 330);
		    	Draw(BLUE,481, 330);
		    	GoTo(482, 331);
		    	Draw(BLUE,482, 331);
		    	GoTo(482, 344);
		    	Draw(BLUE,482, 344);
		    	GoTo(486, 345);				// K
		    	Draw(BLUE,486, 330);
		    	GoTo(492, 345);
		    	Draw(BLUE,487, 338);
		    	GoTo(492, 330);
		    	Draw(BLUE,487, 338);		// END OF FEEDBACK INDICATOR

		    	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    	if(is_feedback_on)
		    	{
		    		GoTo(516, 344);			// O
		    		Draw(BLUE,516, 331);
		    		GoTo(524, 344);
		    		Draw(BLUE,524, 331);
		    		GoTo(517, 345);
		    		Draw(BLUE,523, 345);
		    		GoTo(517, 330);
		    		Draw(BLUE,523, 330);
		    		GoTo(527, 345);				// N
		    		Draw(BLUE,527, 330);
		    		GoTo(534, 345);
		    		Draw(BLUE,534, 330);
		    		GoTo(527, 345);
		    		Draw(BLUE,534, 330);
		    	}
		    	else
		    	{
			    	GoTo(508, 344);				// O
			    	Draw(BLUE,508, 331);
			    	GoTo(516, 344);
			    	Draw(BLUE,516, 331);
			    	GoTo(509, 345);
			    	Draw(BLUE,515, 345);
			    	GoTo(509, 330);
			    	Draw(BLUE,515, 330);
			    	GoTo(520,345);				// F
			    	Draw(BLUE,520, 330);
			    	GoTo(520,345);
			    	Draw(BLUE,527, 345);
			    	GoTo(520,337);
			    	Draw(BLUE,525, 337);
			    	GoTo(520+10,345);			// F
			    	Draw(BLUE,520+10, 330);
			    	GoTo(520+10,345);
			    	Draw(BLUE,527+10, 345);
			    	GoTo(520+10,337);
			    	Draw(BLUE,525+10, 337);
		    	}

		    	if(is_gate_on)
		    	{
					GoTo(516, 344+45);				// O
					Draw(BLUE,516, 331+45);
					GoTo(524, 344+45);
					Draw(BLUE,524, 331+45);
					GoTo(517, 345+45);
					Draw(BLUE,523, 345+45);
					GoTo(517, 330+45);
					Draw(BLUE,523, 330+45);
					GoTo(527, 345+45);				// N
					Draw(BLUE,527, 330+45);
					GoTo(534, 345+45);
					Draw(BLUE,534, 330+45);
					GoTo(527, 345+45);
					Draw(BLUE,534, 330+45);
		    	}
		    	else
		    	{
			    	GoTo(508, 344+45);				// GATE OFF (O)
			    	Draw(BLUE,508, 331+45);
			    	GoTo(516, 344+45);
			    	Draw(BLUE,516, 331+45);
			    	GoTo(509, 345+45);
			    	Draw(BLUE,515, 345+45);
			    	GoTo(509, 330+45);
			    	Draw(BLUE,515, 330+45);
			    	GoTo(520,345+45);				// F
			    	Draw(BLUE,520, 330+45);
			    	GoTo(520,345+45);
			    	Draw(BLUE,527, 345+45);
			    	GoTo(520,337+45);
			    	Draw(BLUE,525, 337+45);
			    	GoTo(520+10,345+45);			// F
			    	Draw(BLUE,520+10, 330+45);
			    	GoTo(520+10,345+45);
			    	Draw(BLUE,527+10, 345+45);
			    	GoTo(520+10,337+45);
			    	Draw(BLUE,525+10, 337+45);
		    	}

		    	return(0);
}

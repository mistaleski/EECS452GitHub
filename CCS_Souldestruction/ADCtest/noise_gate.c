#include "noise_gate.h"

int noise_gate(int input, int threshold, int attack_time_ms, int decay_time_ms, int hold_time_ms)
{

 static int corrected;
 static int state = STATE_IDLE;
 static long attack_time;
 static long decay_time;
 static long hold_time;
 static long ramp_up;
 static long ramp_down;
 static long temp_out;
 static long temp_out2;
 
  switch (state)
 {
     case STATE_IDLE:   if ( input > threshold || -input > threshold )
                         {
                          attack_time = (long) attack_time_ms * SF;
						  ramp_up = attack_time;
                          state = STATE_ATTACK;
                         }
                        else
                         {
                           ; 	// Do nothing
                         }
                      
                        corrected = 0;	// Zero Output
                        break;
               
     case STATE_ATTACK: if (attack_time == 1)
                         {
						  hold_time = (long) hold_time_ms * SF;
                          state = STATE_ACTIVE;		// Ramp is done!
                         }
                        else 
                          {
                            ; 	// Keep decreasing timer
                          } 
                        attack_time--;	// Decrease counter
                        temp_out = (((ramp_up-attack_time)<<16)/ramp_up);
                        temp_out2 = ((temp_out)*(long)input);
                        corrected = (int)(temp_out2>>16);
                        break;
    
     case STATE_ACTIVE: if ( input > threshold || -input > threshold)
						{
    	 	 	 	 	 hold_time = (long) hold_time_ms * SF;
    	 	 	 	 	 state = STATE_ACTIVE;
						}
     	 	 	 	 	else if ( hold_time == 1)
     						{
     						 decay_time = (long) decay_time_ms * SF;
     						 ramp_down = decay_time;
                             state = STATE_DECAY;
     						}

                        else
                         {
                        	hold_time--; 	// Keep decreasing timer
                         }
                        corrected = input;
                        break;
                       
     case STATE_DECAY:  if ( input > threshold || -input > threshold )
                          {
                           attack_time = (long) attack_time_ms * SF;
						   ramp_up = attack_time;
                           state = STATE_ATTACK;
                          }
                        else if (decay_time == 1)
                          {
                           state = STATE_IDLE; 
                          } 
                        else 
                          {
                            ; 	// Keep decreasing timer
                          }
                        decay_time--;
                        temp_out = (((decay_time<<16)/ramp_down));
                        temp_out2 = ((temp_out)*(long)input);
                        corrected = (int)(temp_out2>>16);
                        break;
						
	 default:			state = STATE_IDLE;
						break;
                       
  }                                                 
  return (corrected);
}


int noise_gate_default(int input)
{
	return noise_gate(input, THRESHOLD_DEFAULT, ATTACK_TIME_DEFAULT, DECAY_TIME_DEFAULT, HOLD_TIME_DEFAULT);
}

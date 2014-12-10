#include "recordSweep.h"


/// @param _min_freq is the minimum frequency in Hz
/// @param _max_freq is the maximum frequency in Hz
/// @param in is a 16384 element array that will be loaded with the recorded data
/// @prereq I2S interrupts are disabled
/// @return 0 for success, nonzero for failure (TODO: error checking)
void recordSweep(Uint32 _min_freq, Uint32 _max_freq, Uint32 fs, Int16 *in, Int32 *avg)
{
	Uint32 FTV, FTV_max, step, i, counter;
	Int16 out, left, right;
  	Uint32 min_freq = _min_freq;
  	Uint32 max_freq = _max_freq;

  	// float duration = 0.2;
  	// 48450 // num cycles for loop takes
  	static const Int32 DIV_FACTOR = 9690; // 0.2 * 48450

  	//FTV sweep range calculations
  	FTV = (Uint32)((min_freq*65536UL)/fs)<<16;		// calculate initial FTV value
  	FTV_max = (Uint32)((max_freq*65536UL)/fs)<<16;	// calculate max FTV value
  	step = ((FTV_max-FTV))/(DIV_FACTOR);

  	//Init FTV variables
  	counter = 0;

  	// Pre-tone
  	for(i=0; i<16384; ++i)
  	 {
  		counter = counter + FTV;
  		out = (sinetable[counter>>23]);
  		AIC_write2(out,out);
  		AIC_read2(&left, &right);
  	 }

  	//Generate Sweep
  	for(i=0; i<16384; ++i)
  	{
  		FTV = FTV + step;
  		if(FTV > FTV_max) {
  			//FTV = (Uint32)(min_freq/fs*65536)<<16;
  		}
  		counter = counter + FTV;
  		out = (sinetable[counter>>23]);
  		AIC_write2(out,out);
  		AIC_read2(&left, &right);
  		in[i]= left;
  	}

  	// Post-tone
  	for(i=0; i<16384; ++i)
  	 {
  		counter = counter + FTV;
  		out = (sinetable[counter>>23]);
  		AIC_write2(out,out);
  		AIC_read2(&left, &right);
  	 }

#ifdef SWEEPREC_DEBUG
  	// Playback
  	for(i=0; i<16384; ++i)
  	{
  		AIC_write2(in[i] ,in[i]);
  	}
#endif

	XVGAinit(0);
	processFFT(in, mypOUT, avg);

}


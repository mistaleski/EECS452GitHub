#ifndef THREEBANDFILTERS_H_
#define THREEBANDFILTERS_H_

static const Int32 ThreeBandfilters[30] = {

//f = 20Hz to 80Hz
32768, //B0 
 0, //B1 
 -32768, //B2 
 32768, //A0 
 -65279, //A1 
  32512, //A2 
 
 //f = 80Hz to 500Hz
32768, //B0 
 0, //B1 
 -32768, //B2 
 32768, //A0 
 -63760, //A1 
  31014, //A2 
 
 //f = 500Hz to 5kHz
32768, //B0 
 0, //B1 
 -32768, //B2 
 32768, //A0 
 -49178, //A1 
  17515, //A2 
 
 //f = 5kHz to 10kHz
32768, //B0 
 0, //B1 
 -32768, //B2 
 32768, //A0 
 -28706, //A1 
  16159, //A2 
 
 //f = 10kHz to 20kHz
32768, //B0 
 0, //B1 
 -32768, //B2 
 32768, //A0 
 17887, //A1 
  4314  //A2
   };
#endif /* THREEBANDFILTERS_H_ */
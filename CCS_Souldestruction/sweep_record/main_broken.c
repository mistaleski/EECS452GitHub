#include <usbstk5515.h>
#include <AIC_func.h>
#include <stdio.h>
#include <math.h>
#include <usbstk5515_interrupts.h>
//#include "cheby100N512.h"
#include <Dsplib.h>
#include "XVGA.h"
#include "recordSweep.h"
#include "avgFFT512to6.h"
//#include "FFT.h"

#define FOREVER 1
#define BLUE 2
#define PI 3.14159265

#define TABLE_SIZE  512

void XVGAinit(Uint16);
void GoTo(Uint16 x, Uint16 y);
void Draw(Uint16 color, Uint16 x, Uint16 y);
void InitSpi(void);		// added
void InitSystem(void);	// added
void ConfigPort(void);	// added


#define BUFSIZE 16384
#define fs 48000UL

DATA left, right, out;

Int32 finalAvgs[6];
Int32 finalLog[6];
Int32 myAvg[512];
Int16 mypFFT[16384];
Int16 sweepResult[16384];
DATA AMP;
Uint16 counter = 0;
void Reset();

interrupt void I2S_ISR(){
	AIC_read2(&left, &right);
	AIC_write2(left, left);

	IFR0 &= (1 << I2S_BIT_POS);//Clear interrupt Flag
}

// Setup AIC interrupt routine.
void I2S_interrupt_setup(void)
{
	Uint32 reset_loc = (Uint32)Reset;
	IVPD = reset_loc >> 8;//pointer table points to Reset
	IVPH = reset_loc >> 8;//Ditto

	*((Uint32*)((reset_loc + I2S_ISR_OFFSET)>>1)) = (Uint32)I2S_ISR;

	SYS_EXBUSSEL |= (0x1 << 8);//Set the External bus select SP0Mode to I2S
	IER0 |= (1 << I2S_BIT_POS);//Set up the Global interrupt register to flag on I2S receive flag
	IFR0 &= (1 << I2S_BIT_POS);
}

//Int16 sweepResult[16384];

void main(void)
{
	unsigned int start_switch = 1;

   	_disable_interrupts();
  	USBSTK5515_init();
  	AIC_init();
  	I2S_interrupt_setup();
  	InitSpi();
	XVGAinit(start_switch);
	start_switch = 0;
	XVGAinit(start_switch);

  	recordSweep(40, 20000, fs, sweepResult, myAvg);

  	averageFFT512to6(myAvg, finalAvgs);

	Uint16 j;
	static Uint32 maxL, avgL, totL;
	maxL = 0;
	totL = 0;

	while(1){}
}

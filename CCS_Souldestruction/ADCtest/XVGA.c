/*  EECS 452 XVGA support

    03Dec2002 .. initial Tektronix 4010 version started .. K.Metzger
    22Feb2004 .. updated for EECS 452 .. K.Metzger
    17May2007 .. FPGA specific protocol implemented .. K.Metzger
 
   The primitive operations derive from pen plotter routines.  penup moves
   the plotting "pen" to a given position in the up (non-printing) position.
   pendn does the same but with the pen in contact with the drawing surface.
   pendot moves pen up and then puts the pen down.  This is like doing a
   penup placing the pen in contact with the drawing surface at the end.

   The display coordinate system has origin in lower left corner of the
   screen.  The full x extent is 1024 points.  The full y extent is 780
   visible points.  These routines work in "raw" coordinates.

*/

#include <usbstk5515.h>
void TX_Put(Uint16);

unsigned pages=0;

void XVGAinit(unsigned int start_switch) 
{
	if(start_switch != 0) {
		pages = 0x0001;
	}
	
	TX_Put(0x8200+pages);    // set work and display pages
	pages = 0x0003&(pages^0x0003);  // switch which is which
	TX_Put(0x8100); // clear working page
    return;
}

void GoTo(int x, int y) 
{
	//x = x*640.0/1024.0+0.5; y=y*480.0/768.0+0.5;
    TX_Put(x&0x03FF);
    TX_Put(0x2000|0x0400|(y&0x03FF));
    return;
}


void Draw(int color, int x, int y) 
{      
	//x=x*640.0/1024.0+0.5; y=y*480.0/768.0+0.5;
	TX_Put(x&0x03FF);
	TX_Put(0x4000|0x0400|((color&0x3)<<11)|(y&0x03FF));    
    return;
}         

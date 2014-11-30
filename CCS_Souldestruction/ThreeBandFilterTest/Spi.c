/* File name: Spi.c

	Simple SPI support for the C5505/C5515.
	Meant for use with the DE2-70 FPGA VGA graphics support.

	25Sep2010 .. initial version .. K.Metzger

*/

#include <usbstk5515.h>
#include <usbstk5515_spi.h>

#define SPI_RST      0x4000
#define SPI_CLKEN    0x8000
#define PCGCR1    *((volatile ioport unsigned *)0x1C02)
#define SPICG     0x0002
#define I2S1CG    0x0200
#define IODIR1      *((volatile ioport unsigned *)0x1C06)
#define PDINHIBR1   *((volatile ioport unsigned *)0x1C17)

void InitSpi(void)
{
   SPICCR = SPI_RST;      // reset the SPI
   SPICCR = 0;            // bring out of reset
   PCGCR1 &= ~SPICG;      // enable the SPI peripheral clock (0 enables) 
   SPICDR = 8;            // set the divide value
   SPICCR = SPI_CLKEN;    // turn on the spi output clock
   SPIDCR1 = 0x0400;      
   SPIDCR2 = 0x0000;
   SPICMD1 = 0x0000;
   
   IODIR1 = 0;
   PDINHIBR1 &= !0x2000;  // enable GPIO 13 pull down
}

void SPIsend(unsigned value)
{
    SPIDAT2 = value;                   		// load value to be sent
    SPICMD2 = 0x107A;                  		// configure and initiate 16-bit transfer
    while ((SPISTAT1 & 0x0004) == 0);  		// wait for transfer to complete
    while (SPIDAT1 !=0) {                   // if VGA FIFO almost full, wait until it isn't
    	SPIDAT2 = 0xFF00;            		// VGA NOP command
        SPICMD2 = 0x107A;                  	// configure and initiate 16-bit transfer
        while ((SPISTAT1 & 0x0004) == 0);  	// wait for transfer to complete
    }
}

void TX_Put(unsigned value)
{
    SPIsend(value);
}

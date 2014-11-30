#define SARCTRL      ((ioport volatile unsigned*)0x7012)
#define SARDATA      ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

#define SW1   0x2A8  // Switch 1 value
#define SW2   0x1FC  // Switch 2 value
#define SW12  0x195  // Switch 1 + 2 value
#define NoKey 0x3FE

// Initializes SAR. borrow from lib
void Init_SAR(void)
{
    *SARCTRL    = 0x3C00;      // Select AIN3, which is GPAIN1
    *SARCLKCTRL = 0x0031;      // 100/50 = 2MHz 
    *SARPINCTRL = 0x7104;
    *SARGPOCTRL = 0; 
    return;
}

// 
// To start an analog to digital conversion the following steps must be executed:
/* 1. Set SAR clock to be less than or equal to 2 MHz in the SAR A/D clock Control Register
(SARCLKCTRL) for fastest conversion rate and operation of the A/D module. 
A/D function clock = (Sys Clk)/(ADCCLKDIV+1) */
/* 2. Write to the SARPINCTRL register (7018h) to power up the SAR circuits and select the SAR reference
voltage. */
// Already done in init

/* 3. Write a 1 to the ADCSTRT bit in the SARCTRL register and the desired channel for the conversion in
the CHSEL bit field. */

void startConversion(Uint8 ch)
{
	SARCTRL = 0x1C00 +  ((0x7 & ch) << 12);
}

/* 4. Read the ADCBUSY bit in the SARDATA register to ensure it is set to 1 to indicate the start of
conversion. Due to delays between the CPU write instruction and the actual write to the SAR A/D
registers the ADCBUSY bit must be set before proceeding. */


/* 5. ADCSTRT in the SARCTRL register and ADCBUSY bit in the SARDATA register are set to 0 to
indicate the end of the conversion sequence. */


/* 6. Once ADCBUSY bit in the SARDATA register is set to 0, the SAR A/D Data Register contains the
channel converted in the CHSEL bit field and the actual converted value in the ADCDAT bit field. */

void conversionISR()
{
	val = *SARDATA;
}

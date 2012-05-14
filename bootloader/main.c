/** C O N F I G U R A T I O N ************************************************/
// Note: For a complete list of the available config pragmas and their values, 
// see the compiler documentation, and/or click "Help --> Topics..." and then 
// select "PIC18 Config Settings" in the Language Tools section.

#pragma config PLLDIV   = 1         // No Divide (4MHz input)
#pragma config CPUDIV   = OSC1_PLL2 // [OSC1/OSC2 Src: /1][96MHz PLL Src /2]
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2

#pragma config FOSC     = XTPLL_XT
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF

#pragma config PWRT     = ON
#pragma config BOR      = ON	  
#pragma config BORV     = 3       // 2.0V
#pragma config VREGEN   = ON      // USB Voltage Regulator

#pragma config WDT      = OFF
#pragma config WDTPS    = 32768

#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF     // PORTB as digital I/O on RESET
#pragma config CCP2MX   = ON      // RC1

#pragma config STVREN   = ON
#pragma config LVP      = OFF
//#pragma config ICPRT	= OFF     // Dedicated In-Circuit Debug/Programming, not available...
#pragma config XINST    = OFF     // Extended Instruction Set

#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CP2      = OFF
#pragma config CP3      = OFF
#pragma config CPB      = OFF
#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRT2     = OFF
#pragma config WRT3     = OFF
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTR2    = OFF
#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system\typedefs.h"                        // Required
#include "system\usb\usb.h"                         // Required
#include "io_cfg.h"                                 // Required

#include "system\usb\usb_compile_time_validation.h" // Optional

/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void bootloader(void);

/** V E C T O R  R E M A P P I N G *******************************************/

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000008
void _high_ISR (void)
{
    _asm goto RM_HIGH_INTERRUPT_VECTOR _endasm
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000018
void _low_ISR (void)
{
    _asm goto RM_LOW_INTERRUPT_VECTOR _endasm
}

#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code

#define TRIGGER_VALUE	0x12u
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/
void main(void)
{
    //Check Bootload Mode Entry Condition
    EEADR = 0xFF;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    if(EEDATA == TRIGGER_VALUE)  // If not enabled, User Mode
    {
        _asm goto RM_RESET_VECTOR _endasm
    }
    EEDATA = TRIGGER_VALUE;
    EECON1bits.WREN = 1;
    StartWrite();
    bootloader();
}

void bootloader(void)
{
    //Bootload Mode
    mInitializeUSBDriver();     // See usbdrv.h
    USBCheckBusStatus();        // Modified to always enable USB module
    for (;;)
    {
        USBDriverService();     // See usbdrv.c
        BootService();          // See boot.c
    }
}

// This function is a dummy firmware that simply forces the system into
// bootloader mode. It is replaced with the real firmware during the
// first firmware update.
#pragma code user = RM_RESET_VECTOR
void _dummy_firmware (void)
{
    // we need some dummy code in here to make this work?
    TRISCbits.TRISC0 = OUTPUT_PIN;
    TRISCbits.TRISC1 = OUTPUT_PIN;
    bootloader();
}

/** EOF main.c ***************************************************************/

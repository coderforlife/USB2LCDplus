/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.2
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 3.11+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 * Rawin Rojvanit       08/14/07    A few updates; added #if defined
 *									sections to support PIC18F87J50
 *									family devices.
 ********************************************************************/

/*********************************************************************
IMPORTANT NOTE: This code is written to work directly on both the
PICDEM FS USB Demo Board, as well as the PIC18F87J50 FS USB Plug-In
Module board.  The code may also be used with your own hardware
platform, but some modifications will be needed.

By default, the code is configured to work with the PICDEM
FS USB Demo board.  When using this board, nothing needs to be
changed.  If using the PIC18F87J50 FS USB Plug-In Module, make the
following changes:

1.  In MPLAB IDE, click "Configure --> Select Device" and then
    select the PIC18F87J50
2.  From the project window, change the linker script to the 
    18f87j50.lkr file
3.  Open usbcfg.h and uncomment the line that reads,
    "//#define PIC18F87J50_FS_USB_PIM" and then comment the other
    choices.

If using this code for other hardware platforms, follow the above
steps (while selecting the appropriate values), but in step #3,
select the "//#define YOUR_BOARD" section instead.  Then attempt to
build the project.  A number of build errors will deliberately occur,
due to the use of the "#error" compiler directive.  Double click on the
error messages and fill in the missing sections with values appropriate
for your hardware platform.

After programming a device with this code, and allowing it to
enumerate for the first time, Windows will ask for a driver. Upon
receiving this prompt, point Windows to the mchpcdc.inf file in the
\MCHPFSUSB\fw\Cdc\inf\win2k_winxp_winvista32 directory.
**********************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system\typedefs.h"                        // Required
#include "system\usb\usb.h"                         // Required
#include "io_cfg.h"                                 // Required

#include "system\usb\usb_compile_time_validation.h" // Optional
#include "user\user.h"                              // Modifiable

/** C O N F I G U R A T I O N ************************************************/
// Note: For a complete list of the available config pragmas and their values, 
// see the compiler documentation, and/or click "Help --> Topics..." and then 
// select "PIC18 Config Settings" in the Language Tools section.
/*
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
*/
/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
void USBTasks(void);

/** V E C T O R  R E M A P P I N G *******************************************/
extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code
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
    InitializeSystem();
    USBTasks();
    UserInit2(); // split these up to help decongest the first one
    for (;;)
    {
        USBTasks();
        ProcessIO();        // See user\user.c & .h
    }
}

/******************************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization routine.
 *                  All required USB initialization routines are called from
 *                  here.
 *
 *                  User application initialization routine should also be
 *                  called from here.                  
 *
 * Note:            None
 *****************************************************************************/
static void InitializeSystem(void)
{
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See io_cfg.h
    #endif

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;
    #endif
    
    mInitializeUSBDriver();         // See usbdrv.h
    UserInit();                     // See user.c & .h
}

/******************************************************************************
 * Function:        void USBTasks(void)
 *
 * PreCondition:    InitializeSystem has been called.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Service loop for USB tasks.
 *
 * Note:            None
 *****************************************************************************/
void USBTasks(void)
{
    /*
     * Servicing Hardware
     */
    USBCheckBusStatus();                    // Must use polling method
    if (UCFGbits.UTEYE != 1u)
    {
        USBDriverService();                 // Interrupt or polling method
    }
    
    #if defined(USB_USE_CDC)
    CDCTxService();
    #endif

}

/** EOF main.c ***************************************************************/

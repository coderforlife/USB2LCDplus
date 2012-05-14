/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.2
 *
 *********************************************************************
 * FileName:        io_cfg.h
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
 * Rawin Rojvanit       05/14/07    Added pin mapping for PIC18F87J50
 *									FS USB Plug In Module board.
 ********************************************************************/

#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/
#include "autofiles\usbcfg.h"

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

// usb-bus sense not used
//#define tris_usb_bus_sense  TRISAbits.TRISA1	// Input
//#if defined(USE_USB_BUS_SENSE_IO)
//#define usb_bus_sense       PORTAbits.RA1
//#else
#define usb_bus_sense       1
//#endif
// self-power sense not used
//#define tris_self_power     TRISAbits.TRISA2    // Input
//#if defined(USE_SELF_POWER_SENSE_IO)
//#define self_power          PORTAbits.RA2
//#else
#define self_power          1					// Used by USBStdGetStatusHandler() in usb9.c
//#endif

#define	CT			PORTBbits.RB0
#define TRISCT		TRISBbits.TRISB0

#define BL			PORTCbits.RC7
#define TRISBL		TRISCbits.TRISC7

#define PWR			PORTAbits.RA0
#define TRISPWR		TRISAbits.TRISA0

#define BUT1		PORTAbits.RA1
#define TRISBUT1	TRISAbits.TRISA1

#define BUT2		PORTAbits.RA2
#define TRISBUT2	TRISAbits.TRISA2

#define BUT3		PORTAbits.RA3
#define TRISBUT3	TRISAbits.TRISA3

#define BUT4		PORTAbits.RA4
#define TRISBUT4	TRISAbits.TRISA4

#define BUT5		PORTAbits.RA5
#define TRISBUT5	TRISAbits.TRISA5

#define OUT1		PORTCbits.RC0
#define TRISOUT1	TRISCbits.TRISC0

#define OUT2		PORTCbits.RC1
#define TRISOUT2	TRISCbits.TRISC1

#define OUT3		PORTCbits.RC2
#define TRISOUT3	TRISCbits.TRISC2

// no more OUT4 or OUT5

#endif //IO_CFG_H

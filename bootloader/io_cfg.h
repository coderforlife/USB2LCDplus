/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        io_cfg.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PICmicro� Microcontroller is intended and
 * supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04     Original.
 ********************************************************************/

/******************************************************************************
 * -io_cfg.h-
 * I/O Configuration File
 * The purpose of this file is to provide a mapping mechanism between
 * pin functions and pin assignments. This provides a layer of abstraction
 * for the firmware code and eases the migration process from one target
 * board design to another.
 *
 *****************************************************************************/

#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/
#include "autofiles\usbcfg.h"

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

/** U S B ***********************************************************/
#define tris_usb_bus_sense  TRISAbits.TRISA1    // Input

#if defined(USE_USB_BUS_SENSE_IO)
#define usb_bus_sense       PORTAbits.RA1
#else
#define usb_bus_sense       1
#endif

#define tris_self_power     TRISAbits.TRISA2    // Input

#if defined(USE_SELF_POWER_SENSE_IO)
#define self_power          PORTAbits.RA2
#else
#define self_power          1
#endif

// For blinking the USB Status
//Uncomment this if you want OUT1-OUT5 to blink the USB status
//#define BLINK_USB_STATUS
#ifdef BLINK_USB_STATUS
#define TRIS_mLED_1 TRISCbits.TRISC0
#define TRIS_mLED_2 TRISCbits.TRISC1
#define TRIS_mLED_3 TRISCbits.TRISC2
#define TRIS_mLED_4 TRISCbits.TRISC6
#define TRIS_mLED_5 TRISCbits.TRISC7

#define mLED_1 PORTCbits.RC0
#define mLED_2 PORTCbits.RC1
#define mLED_3 PORTCbits.RC2
#define mLED_4 PORTCbits.RC6
#define mLED_5 PORTCbits.RC7

#define mLED_1_Off() mLED_1 = 0
#define mLED_1_On()  mLED_1 = 1
#define mLED_2_Off() mLED_2 = 0
#define mLED_2_On()  mLED_2 = 1
#define mLED_1_Toggle() mLED_1 = !mLED_1
#define mLED_2_Toggle() mLED_2 = !mLED_2
#endif

#endif //IO_CFG_H

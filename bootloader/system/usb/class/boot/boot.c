/*********************************************************************
 *
 *      Microchip USB C18 Firmware -  USB Bootloader Version 1.00
 *
 *********************************************************************
 * FileName:        boot.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
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
 * Rawin Rojvanit       11/19/04    Original. USB Bootloader
 ********************************************************************/

/******************************************************************************
 * -boot.c-
 * This file contains functions necessary to carry out bootloading tasks.
 * The only 2 USB specific functions are BootInitEP() and BootService().
 * All other functions can be reused with other communication methods.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"
#include <eep.h>

/** V A R I A B L E S ********************************************************/
#pragma udata
byte counter;
byte byteTemp;
byte trf_state;
rom far char *addr;
word count;

word big_counter;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
#ifdef BLINK_USB_STATUS
void BlinkUSBStatus(void);
#endif

/** D E C L A R A T I O N S **************************************************/
#pragma code

/** C L A S S  S P E C I F I C  R E Q ****************************************/

/** U S E R  A P I ***********************************************************/

/******************************************************************************
 * Function:        void BootInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BootInitEP initializes bootloader endpoints, buffer
 *                  descriptors, internal state-machine, and variables.
 *                  It should be called after the USB host has sent out a
 *                  SET_CONFIGURATION request.
 *                  See USBStdSetCfgHandler() in usb9.c for examples.
 *
 * Note:            None
 *****************************************************************************/
void BootInitEP(void)
{   
    trf_state = WAIT_FOR_CMD;
    BOOT_UEP = EP_OUT_IN|HSHK_EN;               // Enable 2 data pipes
    count = 0;

    /*
     * Do not have to init Cnt of IN pipes here.
     * Reason:  Number of bytes to send to the host
     *          varies from one transaction to
     *          another. Cnt should equal the exact
     *          number of bytes to transmit for
     *          a given IN transaction.
     *          This number of bytes will only
     *          be known right before the data is
     *          sent.
     */
    BOOT_BD_OUT.Cnt = sizeof(dataPacket);   // Set buffer size
    BOOT_BD_OUT.ADR = (byte*)&dataPacket;   // Set buffer address
    BOOT_BD_OUT.Stat._byte = _USIE|_DAT0|_DTSEN;// Set status

    BOOT_BD_IN.ADR = (byte*)&dataPacket;    // Set buffer address
    BOOT_BD_IN.Stat._byte = _UCPU|_DAT1;    // Set buffer status

    #ifdef BLINK_USB_STATUS
    TRIS_mLED_1 = OUTPUT_PIN;
    TRIS_mLED_2 = OUTPUT_PIN;
    TRIS_mLED_3 = OUTPUT_PIN;
    TRIS_mLED_4 = OUTPUT_PIN;
    TRIS_mLED_5 = OUTPUT_PIN;
    #endif
}

void StartWrite(void)
{
    /* A write command can be prematurely terminated by MCLR or WDT reset */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1_WR = 1;
}

void ReadVersion(void) //TESTED: Passed
{
    Busy_eep();
    dataPacket.bytes[2] = Read_b_eep(EEP_SER_NUM_0);
    dataPacket.bytes[3] = Read_b_eep(EEP_SER_NUM_1);
    dataPacket.bytes[4] = MAJOR_VERSION;
    dataPacket.bytes[5] = MINOR_VERSION;
}

void StartWriteProgMem(void)
{
    addr = dataPacket.addr;
    count = dataPacket.count;
}

void WriteProgMem(void)
{
    // erase chunk first
    EECON1 = 0b10010100;
    *(addr);
    StartWrite();
    TBLPTRU = 0;

    EECON1 = 0b10000100; //Setup writes: EEPGD=1,WREN=1
    for (counter = 0; counter < 64u; counter++)
    {
        *(addr+counter) = dataPacket.bytes[counter];
        if ((counter & 0b00011111) == 0b00011111u)
        {
            StartWrite();
        }
    }
}

void BootService(void)
{
    #ifdef BLINK_USB_STATUS
    BlinkUSBStatus();
    #endif
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1u)) return;

    if(trf_state == SENDING_RESP)
    {
        if(!mBootTxIsBusy())
        {
            BOOT_BD_OUT.Cnt = sizeof(dataPacket);
            mUSBBufferReady(BOOT_BD_OUT);
            trf_state = WAIT_FOR_CMD;
        }
        return;
    }
    
    if(!mBootRxIsBusy())
    {
        counter = 0;
        if (count)
        {
            WriteProgMem();
            --count;
            dataPacket.CMD = WRITE_FLASH;
            dataPacket.len = 7;
            dataPacket.addr = addr;
            dataPacket.count = count;
            addr += 64;
            counter=0x07;
        }
        else
        {
            switch(dataPacket.CMD)
            {
                case READ_VERSION:
                    ReadVersion();
                    counter=0x06;
                    break;

                case WRITE_FLASH:
                    StartWriteProgMem();
                    counter=0x01;
                    break;

                case RESET:
                    //When resetting, make sure to drop the device off the bus
                    //for a period of time. Helps when the device is suspended.
                    UCONbits.USBEN = 0;
                    big_counter = 0;
                    while(--big_counter);
                    Reset();
                    break;

                default:
                    break;
            }
        }
        trf_state = SENDING_RESP;
        if(counter != 0u)
        {
            BOOT_BD_IN.Cnt = counter;
            mUSBBufferReady(BOOT_BD_IN);
        }
    }
}

#ifdef BLINK_USB_STATUS
void BlinkUSBStatus(void)
{
    static word led_count=0;
    
    if(led_count == 0u) led_count = 20000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(UCONbits.SUSPND == 1u)
    {
        if(led_count==0u)
        {
            mLED_1_Toggle();
            mLED_2 = mLED_1;        // Both blink at the same time
        }
    }
    else
    {
        if(usb_device_state == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(usb_device_state == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(usb_device_state == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(usb_device_state == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(usb_device_state == ADDRESS_STATE)
        {
            if(led_count == 0u)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }
        }
        else if(usb_device_state == CONFIGURED_STATE)
        {
            if(led_count==0u)
            {
                mLED_1_Toggle();
                mLED_2 = !mLED_1;       // Alternate blink                
            }
        }
    }
}
#endif

/** EOF boot.c ***************************************************************/

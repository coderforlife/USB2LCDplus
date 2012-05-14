USB2LCD+
========

PIC18 USB Controller for HD44780 character LCDs.

Some of this code is based on code by ch424.  
The xlcd library is only slightly modified from the code given by Microchip.

The important files are:
* xlcd.h - Header file for lcd functions
* lcd\\\* - C files for lcd functions (not all are used)
* main.c - Programmer config, main controling functions (programming config is ignored when using bootloader)
* io_cfg.h - Defines the pins that will be used for what
* user\user.h - Public functions from user.c
* user\user.c - The bulk of the code is here
 * `UserInit#()` are called at bootup
 * `ProcessIO()` is called during every iteration
* user\cmds.h - Includes tons of defines setting up LCD commands, serial commands, EEPROM storage locations
* system\interrupt\interrupt.c - The high and low interrupt functions

Within bootloader:
* main.c - Programmer config, main controling functions, startup sequence, interrupt forwards, and dummy firmware
* io_cfg.h - Defines the pins that will be used for what (has a #define to enable a diagnostic `BlinkUSBStatus`)
* system\usb\class\boot\\\* - The bootloader main code. This has code for updating the firmware. These functions are heavily based on the Microchip provided bootloader.
 * `BootInitEP()` is called at bootup
 * `BootService()` is called during every USB iteration

The files autofiles\\\*, system\typedefs.h, system\usb\\\* are the files provided by Microchip USB Core.

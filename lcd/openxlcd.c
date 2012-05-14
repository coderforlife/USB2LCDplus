#include <p18cxxx.h>
#include <xlcd.h>

/********************************************************************
*       Function Name:  OpenXLCD                                    *
*       Return Value:   void                                        *
*       Parameters:     lcdtype: sets the type of LCD (lines)       *
*       Description:    This routine configures the LCD. Based on   *
*                       the Hitachi HD44780 LCD controller. The     *
*                       routine will configure the I/O pins of the  *
*                       microcontroller, setup the LCD for 4- or    *
*                       8-bit mode and clear the display. The user  *
*                       must provide three delay routines:          *
*                       DelayFor18TCY() provides a 18 Tcy delay     *
*                       DelayPORXLCD() provides at least 15ms delay *
*                       DelayXLCD() provides at least 5ms delay     *
********************************************************************/
void OpenXLCD_1(void)
{
        // The data bits must be either a 8-bit port or the upper or
        // lower 4-bits of a port. These pins are made into inputs
#ifdef BIT8                             // 8-bit mode, use whole port
        DATA_PORT = 0;
        TRIS_DATA_PORT = 0xff;
#else                                   // 4-bit mode
#ifdef UPPER                            // Upper 4-bits of the port
        DATA_PORT &= 0x0f;
        TRIS_DATA_PORT |= 0xf0;
#else                                   // Lower 4-bits of the port
        DATA_PORT &= 0xf0;
        TRIS_DATA_PORT |= 0x0f;
#endif
#endif
        TRIS_RW = 0;                    // All control signals made outputs
        TRIS_RS = 0;
        TRIS_E = 0;
        RW_PIN = 0;                     // R/W pin made low
        RS_PIN = 0;                     // Register select pin made low
        E_PIN = 0;                      // Clock pin made low
}

void OpenXLCD_2(unsigned char lcdtype)
{
        // Delay for 15ms to allow for LCD Power on reset
        DelayPORXLCD();
        
        // Setup interface to LCD
#ifdef BIT8                             // 8-bit mode interface
        TRIS_DATA_PORT = 0;             // Data port output
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit mode interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= 0b00100000;        // Function set cmd(4-bit interface)
#else                                   // Lower nibble interface
        TRIS_DATA_PORT &= 0xf0;
        DATA_PORT &= 0xf0;
        DATA_PORT |= 0b00000010;        // Function set cmd(4-bit interface)
#endif
#endif
        E_PIN = 1;                      // Clock the cmd in
        DelayFor18TCY();
        E_PIN = 0;
        
        // Delay for at least 4.1ms
        DelayXLCD5ms();

        // Setup interface to LCD
#ifdef BIT8                             // 8-bit interface
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00100000;
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00000010;
#endif
#endif
        E_PIN = 1;                      // Clock the cmd in
        DelayFor18TCY();
        E_PIN = 0;

        // Delay for at least 100us
        DelayXLCD100();

        // Setup interface to LCD
#ifdef BIT8                             // 8-bit interface
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00100000;
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00000010;
#endif
#endif
        E_PIN = 1;                      // Clock cmd in
        DelayFor18TCY();
        E_PIN = 0;

#ifdef BIT8                             // 8-bit interface
        TRIS_DATA_PORT = 0xff;          // Make data port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT |= 0xf0;         // Make data nibble input
#else                                   // Lower nibble interface
        TRIS_DATA_PORT |= 0x0f;         // Make data nibble input
#endif
#endif

        // Set data interface width, # lines, font
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(lcdtype);          // Function set cmd

        // Turn the display off then on
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
        //while(BusyXLCD());              // Wait if LCD busy
        //WriteCmdXLCD(DON);              // Display ON/Blink ON

        // Clear display
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0x01);             // Clear display

        // Set entry mode inc, no shift
        while(BusyXLCD());              // Wait if LCD busy
        //WriteCmdXLCD(SHIFT_CUR_LEFT);   // Entry Mode
        WriteCmdXLCD(0b00000110);		// Entry mode: move cursor right on write/read

        // Set DD Ram address to 0
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0b10000000);       // Set Display data ram address to 0

        return;
}


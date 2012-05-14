#include <p18cxxx.h>
#include "xlcd.h"

/********************************************************************
*       Function Name:  SendDataXLCD                                *
*       Return Value:   void                                        *
*       Parameters:     lcd: LCD_1, LCD_2, or LCD_BOTH              *
*       Description:    This is used to send a pending command or   *
*                       data to the LCD (and handles multiple LCD   *
*                       controllers).                               *
********************************************************************/
void SendDataXLCD(unsigned char lcd)
{
	DelayFor18TCY();
	E1_PIN = (lcd & LCD_1);
	E2_PIN = (lcd & LCD_2);
	DelayFor18TCY();
	E1_PIN = E2_PIN = 0;
}

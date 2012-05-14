#ifndef _CMDS_H_
#define _CMDS_H_


/**
 * LCD Types, used by EEP_LCD_TYPE, SET_LCD_TYPE, SetLCDType, GetLCDType
 */
#define LCD_NONE		0u
#define LCD_HD44780		1u // Also supports KS0066U and maybe KS0073
#define LCD_DBL_HD44780	2u // Double HD44780 (4x40)
#define LCD_16X4PT		3u // Uses different positions but otherwise the same as HD44780
//#define LCD_T6963C
//#define LCD_KS0066FF00


/**
 * LCD Commands
 */
#define LCD_CLEAR		0b00000001
#define LCD_HOME		0b00000010
//#define LCD_ENTRY_MODE 0b00000100	// I don't know how to really use this one...
#define LCD_DISP_CTL	0b00001111	// the last 3 digits are for display, blink, and cursor
#define LCD_CUR_LEFT	0b00010000
#define LCD_CUR_RIGHT	0b00010100
#define LCD_SFT_LEFT	0b00011000	// shift text left
#define LCD_SFT_RIGHT	0b00011100	// shift text right
//#define LCD_FUNC_SET	0b00100000
#define LCD_CUST_CHAR_	0b01000000
#define LCD_CUST_CHAR(b) LCD_CUST_CHAR_+8*b	// the command to go to the b-th custom character


/**
 * EEPROM Memory Locations
 */
// We have max 256 bytes, this uses 0x00-0xF0, 0xFE-0xFF (0-240, 254-255), there are ~14 bytes left
#define EEP_DISPLAY		0x00u // display, cursor, and blink
#define EEP_DISPLAY_MIN	0x01u
#define EEP_BACKLIGHT	0x02u
#define EEP_CONTRAST	0x03u

// this could be all one byte (saves 4 bytes)
#define EEP_GPO_0		0x04u
#define EEP_GPO_1		0x05u
#define EEP_GPO_2		0x06u
#define EEP_GPO_3		0x07u
#define EEP_GPO_4		0x08u
#define EEP_GPO(x)		EEP_GPO_0+x

#define EEP_GPO_PWM_0	0x09u
#define EEP_GPO_PWM_1	0x0Au
#define EEP_GPO_PWM_2	0x0Bu
#define EEP_GPO_PWM_3	0x0Cu
#define EEP_GPO_PWM_4	0x0Du
#define EEP_GPO_PWM(x)	EEP_GPO_PWM_0+x

#define EEP_SER_NUM_0	0x0Eu
#define EEP_SER_NUM_1	0x0Fu

#define EEP_CHAR_0		0x10u
#define EEP_CHAR_1		0x18u
#define EEP_CHAR_2		0x20u
#define EEP_CHAR_3		0x28u
#define EEP_CHAR_4		0x30u
#define EEP_CHAR_5		0x38u
#define EEP_CHAR_6		0x40u
#define EEP_CHAR_7		0x48u
#define EEP_CHAR(x)		EEP_CHAR_0+8*x	// get character x
#define EEP_CHAR_B(x,b)	EEP_CHAR(x)+b	// get the b-th byte of character x

#define EEP_MSG_START	0x50u
#define EEP_LINE_0		0x50u
#define EEP_LINE_1		0x78u
#define EEP_LINE_2		0xA0u
#define EEP_LINE_3		0xC8u
#define EEP_LINE(x)		EEP_MSG_START+20*x
#define EEP_MSG(x,c)	EEP_LINE(x)+c	// the c-th character on the x-th line

#define EEP_LCD_TYPE	0xFE // normal, large, and others

#define EEP_FIRMWARE	0xFF // this byte is set to 1 when the firmware will be reprogrammed after a RESET


/**
 * Commands stored in next_cmd and handled by doCommand()
 */
#define NONE		 0u // vast majority of the time
#define CMD			 1u // next item will be a command handled by doCommand2()

#define POS_COL		10u // position col
#define POS_ROW		11u // position row

#define CUST_C		12u // custom character character number
#define CUST_X		13u // custom character bytes 1-8

#define DISPLAY		21u // display mins
#define BACKLIGHT	22u // backlight pwm
#define CONTRAST	23u // contrast wpm

#define GPO_ON		24u	// GPO on index
#define GPO_OFF		25u	// GPO off index
#define GPO_PWM_IND	26u	// GPO PWM index
#define GPO_PWM		27u	// GPO PWM

#define READ_BUT	29u	// the button index to read

#define REMEMBER	30u // remember on or off
#define REM_BCKLGHT	31u	// remember backlight
#define REM_GPO_IND	32u // remember GPO
#define REM_GPO_PWM	33u // remember GPO PWM
#define REM_GPO 	34u // remember GPO
#define REM_GPO_ON 	35u // remember GPO on/off state
#define REM_STARTUP	36u // remember a startup screen, bytes 1-80

#define REM_CUST_C	40u // remember custom character character number
#define REM_CUST_1	41u // remember custom character byte 1
#define REM_CUST_2	42u // remember custom character byte 2
#define REM_CUST_3	43u // remember custom character byte 3
#define REM_CUST_4	44u // remember custom character byte 4
#define REM_CUST_5	45u // remember custom character byte 5
#define REM_CUST_6	46u // remember custom character byte 6
#define REM_CUST_7	47u // remember custom character byte 7
#define REM_CUST_8	48u // remember custom character byte 8

#define	READ_C_CUST	50u	// read current custom character
#define READ_C_GPO	51u // read current GPO
#define READ_C_GPOP	52u // read current GPO PWM
#define	READ_S_CUST	53u	// read saved custom character
#define READ_S_GPO	54u // read saved GPO
#define READ_S_GPOP	55u // read saved GPO PWM

#define SER_NUM_1	60u	// set serial number byte 1
#define SER_NUM_2	61u	// set serial number byte 2

#define SET_LCD_TYPE	62u // set the large display value


/**
 * Commands that are sent by the computer.
 * These are handled in doCommand2().
 * These are the numbers to send to run these commands.
 */
#define Firmware			  1u // 3 seconds afterward the device will reset go into a special boot-up mode where the firmware can be reprogrammed
#define PORDevice			  2u // Resets device in 3 seconds
#define ReadDisplay			  3u // Returns 1 byte, with the 3 LSB being the current display, cursor and blink
#define ReadDisplayMin		  4u // Returns 1 byte, the current remaining time till display off, or 0
#define ReadContrast		  5u // Returns 1 byte, the current contrast level
#define ReadBacklight		  6u // Returns 1 byte, the current backlight level
#define ReadCustom			  7u // [char:0-7] Returns 8 bytes, the 8 bytes of the custom char
#define ReadMessage			  8u // Returns 80 bytes, the current message
#define ReadGPO				  9u // [1-5] Returns 1 byte, the current state of the GPO
#define ReadGPOpwm			 10u // [1-5] Returns 1 byte, the current pwm of the GPO
#define ReadSavedDisplay	 13u // Returns 1 byte, with the 3 LSB being the saved display, cursor and blink
#define ReadSavedDisplayMin	 14u // Returns 1 byte, the saved time till display off, or 0
#define ReadSavedContrast	 15u // Returns 1 byte, the saved contrast level
#define ReadSavedBacklight	 16u // Returns 1 byte, the saved backlight level
#define ReadSavedCustom		 17u // [char:0-7] Returns 8 bytes, the 8 bytes of the saved char
#define ReadSavedMessage	 18u // Returns 80 bytes, the (beginning of the) saved startup message
#define ReadSavedGPO		 19u // [1-5] Returns 1 byte, the current state of the GPO
#define ReadSavedGPOpwm		 20u // [1-5] Returns 1 byte, the current pwm of the GPO
#define SetSerialNum		 52u // [2 bytes], can be called any number of times
#define ReadSerialNum		 53u // Returns 2 bytes
#define ReadVersion			 54u // Returns 1 byte, the version of the firmware (major version in high nibble, minor version in low nibble)
#define ReadModuleType		 55u // Returns 1 byte, exactly 0x5B to identify this software
#define SaveStartup			 64u // [80 chars] (spec says 40, but we want to be able to use 20x4)
#define DisplayOn			 66u // [mins:0-255]
#define DisplayOff			 70u
#define Position			 71u // [col:1-20][row:1-4]
#define Home				 72u
#define CursorOn			 74u
#define CursorOff			 75u
#define CursorLeft			 76u
#define CursorRight			 77u
#define DefineCustom		 78u // [char:0-7][8 bytes], effects both LCD halves
#define Contrast			 80u // [0-255]
#define BlinkOn				 83u
#define BlinkOff			 84u
#define GPOoff				 86u // [1-5]
#define GPOon				 87u // [1-5]
#define ClearDisplay		 88u
#define Backlight_			 89u // [0-255], duplicate of 152
#define GPOpwm				102u // [1-5][0-255]
#define SaveBacklight		145u // [0-255]
#define Remember			147u // [0-1]
#define Backlight			152u // [0-255]
#define GPOpwm_				192u // [1-5][0-255], duplicate of 102
#define ReadButton			193u // [1-5], returns one character A-E (this is originally for reading fan RPM)
#define RememberCustom		194u // [char:0-7][8 bytes], effects both LCD halves
#define RememberGPOpwm		195u // [1-5][0-255]
#define RememberGPO			196u // [1-5][0-1]
#define Char254				254u

// Commands added in version 2 (support for 40x4 LCDs)
// All commands ending with '2' will do nothing if GetLCDType is not a large display (such as LCD_DBL_HD44780)
#define SetLCDType			 21u // [1 byte] see LCD_* for values, defaults to LCD_NONE if not understood; this setting is always remembered
#define GetLCDType			 22u // Return 1 byte, one of the LCD_* values
#define ReadMessage2		 23u // Returns 80 bytes, the end of the current message
#define ReadSavedMessage2	 24u // Returns 80 bytes, the end of the saved startup message
#define SaveStartup2	 	 25u // [80 chars] the end of the startup message to save
//#define DefineCustom2		 26u // [lcd:0-1][char:0-7][8 bytes], effects only one LCD half, top for lcd=0, bottom otherwise
//#define ReadCustom2		 27u // [char:0-7] Returns 8 bytes, the 8 bytes of the custom char from the bottom half of the display
//#define RememberCustom2	 28u // [lcd:0-1][char:0-7][8 bytes], effects only one LCD half, top for lcd=0, bottom otherwise ! Probably don't have room to save

#endif
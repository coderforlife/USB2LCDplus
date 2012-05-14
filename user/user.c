/* USB2LCD+ Main Program File

v1.0 Initial Release
v1.1 
    Reorganized startup message code to prevent the startup message from showing while the computer is off or USB is suspended
    Reorganized the BL / CT / GPO updating code to allow it to run before the computer has fully turned on
    Made it so the interrupt timer is off whenever it is not needed (not waiting for the display to turn off)
    Fixed the reset command so that time is given for the host to close the serial port (3 seconds)
    Added a firmware reprogramming command that sets an EEPROM bit and resets to let the bootloader do its thing
    Modified the program to allow a bootloader to fit in the first 0x800 bytes
v1.2
    Added serial number setting / reading
    Fixed the numbering of the read version and read module type (they were one off before)
v1.3
    Added the ability to use a rotary input instead of buttons for buttons 1 and 2


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>			// Microchip definitions
#include "io_cfg.h"             // I/O pin mapping
#include "user\user.h"			// Public Function Prototype
#include "system\typedefs.h"	// Typedefs (I use byte and BOOL mostly)
#include <timers.h>				// Timer functions
#include <delays.h>				// Delay functions
#include <eep.h>				// EEPROM functions - persistent memory
#include "xlcd.h"				// LCD functions
#include "system\usb\usb.h"		// USB functions

#include "cmds.h"				// Commands definitions

#define BUSY_LCD()	while (BusyXLCD()); // Use this to wait for the LCD to become not busy

/** V A R I A B L E S ********************************************************/
#pragma udata

#define VERSION 0x13	// Firmware version (v1.3)
#define MODULE  0x5B	// Module version (looks like S and B of USB)

#define BUFFER_LEN 80u	// Enough to fit a whole 4x20 message in the buffer...

char input_buffer[BUFFER_LEN];	// The input buffer
byte input_buffer_pos;			// Current read position from buffer
byte input_buffer_size;			// Current amount of valid data in buffer
byte cur_byte;					// Most recently read byte from buffer
byte saved_byte;				// A byte that certain operations use to save data temporarily
byte next_cmd;					// The next command to run

byte output_buffer[BUFFER_LEN];	// The output buffer
byte output_buffer_pos;			// The current position in the output buffer

BOOL remember;					// True if we should remember (save to EEPROM) changes to the LCD screen

byte secsx;		// not quite seconds, about 43 of them per minute
byte counter;	// know how many iterations we have done

BOOL resetting;	// true when resetting the device
BOOL powered_down;

/*
The PWMs work by quickly alternating a pin between 1 and 0. To increase the apparent frequency of
the PWM the 1s and 0s are made to be as evenly distributed as possible (so 11110000 would be better
as 10101010). This means we can reduce flicker without raising the real frequency, but instead
"simulate" a higher frequency. Some nice patterns show up that make setting up this structure
fairly easy, and it is 100% accurate. See setPWM() and updatePWM() for more information.
*/
// A structure for saving PWM data, takes a total of 9 bytes
typedef struct _pwm {
    struct pwm_part {
        byte repeat;	// the number of times to repeat this part
        byte ones;		// the number of ones in this part
        byte total;		// the number of ones + zeroes in this part
    } parts[2];
    byte cur_part;		// either part 0 or 1
    byte cur_repeat;	// the number of times that part has already run
    byte cur;			// the current position in that part
} pwm;

// Advances a pwm structure 1 position and returns a 1 if the target should be on and a 0 if it should be off this cycle
#define PWM_ADVANCE(x)		((++x.cur < x.parts[x.cur_part].total || updatePWM(&x)) && x.cur < x.parts[x.cur_part].ones)
// Determines if a pwm structure always returns 0
#define PWM_ALWAYS_OFF(x)	(x.parts[0].ones == 0u)
// Determines if a pwm structure always returns 1
#define PWM_ALWAYS_ON(x)	(x.parts[0].ones == 255u)
// Returns the value (out of 255) for the pwm structure
#define PWM_VALUE(x)		((((unsigned long)x.parts[0].repeat)*x.parts[0].ones+((unsigned long)x.parts[1].repeat)*x.parts[1].ones)*255ul/(((unsigned long)x.parts[0].repeat)*x.parts[0].total+((unsigned long)x.parts[1].repeat)*x.parts[1].total))

byte onFor;			// number of minutes left to keep the display on, or 0 for forever
pwm backlight;		// the backlight pwm
pwm contrast;		// the contrast pwm

// the state of the display, cursor, and blink bits, takes a total of 1 byte
union _dcb_state {
    byte bits;
    struct {
        unsigned blink:   1;
        unsigned cursor:  1;
        unsigned display: 1;
        unsigned: 5; // always 00001, see LCD_DISP_CTL
    };
} DCB_state; // display, cursor, blink state

pwm gpo_pwm[5];		// the GPO pwms
BOOL gpo[5];		// the GPO on/off states

// the state of the 5 buttons, takes a total of 1 byte
union _buttons { // 1 byte
    byte bits;
    struct {
        unsigned:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned :2;
    };
    struct {
        unsigned:1;
        unsigned rotary:2;
        unsigned:5;
    };
} buttons;

char last_rotation = 'L';

// returns 1 if a button is currently pressed
#define IS_PRESSED(x)	(!BUT##x##)
// returns 1 if a button is currently pressed but not pressed according to the buttons variable
#define JUST_PRESSED(x)	(!buttons.b##x##&&IS_PRESSED(x))
// returns 1 if a button is not currently pressed but is pressed according to the buttons variable
#define JUST_LET_GO(x) 	(buttons.b##x##&&!IS_PRESSED(x))
// if the current byte is x, then it writes a to the serial port if x is currently pressed or the lowercase version if it is not pressed
#define DO_PRESSED(x,a)	if (cur_byte==x##u##) { put(IS_PRESSED(x) ? a : (a+32)); }
// checks the state of the button x, updates the buttons variable, and writes the change to the serial port
#define CHECK_BUTTON(x,a) \
    if (JUST_PRESSED(x))		{ buttons.b##x## = 1; /*gpo[x-1] = 1; refreshGPO(x-1);*/ put(a); } \
    else if (JUST_LET_GO(x))	{ buttons.b##x## = 0; /*gpo[x-1] = 0; refreshGPO(x-1);*/ put(a+32); }

// get the current rotary value
#define CUR_ROTARY()	(((!BUT1) << 1) | (!BUT2))
// get the previous rotary value
#define PREV_ROTARY()	(buttons.rotary)

/** P R I V A T E  P R O T O T Y P E S ***************************************/

BOOL getNextByte(void);
void doCommand(void);
void doCommand2(void);
void LCDGoto(byte col, byte row);
void RememberIt(const unsigned int add, const byte data);
void setPWM(byte x, pwm *p);
BOOL updatePWM(pwm *p);
void refreshGPO(byte x);
void reset(void); // this function simply goes to the macro Reset(), made a separate function so the code can still be optimized
void resetInit(void);
void firmwareReprogramInit(void);

/** D E C L A R A T I O N S **************************************************/
#pragma code

// Defined for use by the LCD module
void DelayFor18TCY(void) { // 18 clock cycles
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); // but at our slow clock time 6 should be fine (500 ns)
}
void DelayPORXLCD(void) { Delay10KTCYx(30); } // actually 25ms (works MUCH better) // 15 ms, running at 48 MHz -> 12 MHz, so 180k
void DelayXLCD5ms(void) { Delay10KTCYx(6); } // 5 ms, running at 48 MHz -> 12 MHz, so 60k
void DelayXLCD100(void) { Delay1KTCYx(12); } // 100 us, so 12k


// Writes to EEPROM if remember is set
// add = address to write to, data = byte to write
void RememberIt(const unsigned int add, const byte data) { if (remember) { Busy_eep(); Write_b_eep(add, data); } }


// Append a byte to the output buffer
#define put(x) (output_buffer_pos < BUFFER_LEN) && (output_buffer[output_buffer_pos++] = x)
// Append n bytes from LCD to the output buffer
void lcd2out(byte n) { while (n--) { BUSY_LCD(); put(ReadDataXLCD()); } }
// Append the bytes from EEPROM between start and end to the output buffer
void eeprom2out(byte start, byte end) { while (start < end) { Busy_eep(); put(Read_b_eep(start++)); } }


// The first round of initialization for the program (there is a lot of initialization to do and we don't want the USB to get mad)
// The pins are all setup, variables are initialized
void UserInit(void) {
    PORTA				= 0;
    ADCON1				= 0x0F;	//all AN pins configured as digital
    CMCON				= 0x07;	//turn porta comparators off
    INTCON2bits.RBPU	= 0;	//portb pullups off
    TRISCT				= OUTPUT_PIN;
    TRISBL				= OUTPUT_PIN;
    BL					= 0;	//both initially off
    CT					= 0;
    TRISBUT1			= INPUT_PIN;
    TRISBUT2			= INPUT_PIN;
    TRISBUT3			= INPUT_PIN;
    TRISBUT4			= INPUT_PIN;
    TRISBUT5			= INPUT_PIN;
    TRISOUT1			= OUTPUT_PIN;
    TRISOUT2			= OUTPUT_PIN;
    TRISOUT3			= OUTPUT_PIN;
    TRISOUT4			= OUTPUT_PIN;
    TRISOUT5			= OUTPUT_PIN;
    OUT1				= 0;	//all initially off
    OUT2				= 0;
    OUT3				= 0;
    OUT4				= 0;
    OUT5				= 0;

    remember			= FALSE;	//initially no remembering
    next_cmd			= NONE;
    buttons.bits		= 0;
    DCB_state.bits		= LCD_DISP_CTL;
    resetting			= FALSE;
    powered_down		= TRUE;

    // Setup the buffers
    input_buffer_pos	= 0;
    input_buffer_size	= 0;
    output_buffer_pos	= 0;

    // Setup the timer (but don't turn it on)
    OpenTimer0(TIMER_INT_ON & T0_SOURCE_INT & T0_16BIT & T0_PS_1_256);

    // Do the basic LCD setup (setup pins)
    OpenXLCD_1();
}//end UserInit

// The second round of initialization for the program
void UserInit2(void) {
    // Initialize the LCD (takes ~35 ms)
    // This sets up the display to be off, cleared, left shifting, at address DRAM 0
    OpenXLCD_2(FOUR_BIT & LINES_5X7);
}

/******************************************************************************
 * Function:        void ProcessIO(void)
 *
 * Overview:        This function is a place holder for other user routines.
 *                  It is a mixture of both USB and non-USB tasks.
 *
 *****************************************************************************/
void ProcessIO(void)
{
    byte i, j, x;

    if (resetting && onFor == 1u) { // last 1 second have USB disabled while resetting
        UCONbits.USBEN = 0;
        powered_down = TRUE;
        while (!secsx) { /*last 'second'*/ }
        INTCONbits.GIE = 0;
        reset();
        return;
    }

    if ((usb_device_state < DEFAULT_STATE || UCONbits.SUSPND) &&	// detached/suspended (but apparently has the power lines active)
        !(usb_device_state == DEFAULT_STATE && UCONbits.SUSPND)) {  // but not during boot-up
        if (!powered_down) {
            // turn off backlight and outputs	
            BL = 0;
            OUT1 = 0;
            OUT2 = 0;
            OUT3 = 0;
            OUT4 = 0;
            OUT5 = 0;
            // turn off display
            DCB_state.display = 0;
            BUSY_LCD();
            WriteCmdXLCD(DCB_state.bits);
            // turn off timer
            INTCONbits.GIE = 0;
            powered_down = TRUE;
        }
        return;
    }

    if (powered_down) { // was just plugged in or just resumed from suspension
        // Read in startup defaults
        Busy_eep();
        DCB_state.bits = Read_b_eep(EEP_DISPLAY) & LCD_DISP_CTL;
        onFor = Read_b_eep(EEP_DISPLAY_MIN);
        setPWM(Read_b_eep(EEP_BACKLIGHT), &backlight);
        setPWM((255-Read_b_eep(EEP_CONTRAST))/2, &contrast);
        for (i = 0; i < 5u; i++) {
            Busy_eep();
            setPWM(Read_b_eep(EEP_GPO_PWM(i)), gpo_pwm+i);
            gpo[i] = Read_b_eep(EEP_GPO(i)) > 0u;
        }

        // Set defaults to LCD
        BUSY_LCD();
        WriteCmdXLCD(DCB_state.bits);

        // Set the default custom characters
        for (i = 0; i < 8u; ++i) {
            BUSY_LCD();
            WriteCmdXLCD(LCD_CUST_CHAR(i));
            x = EEP_CHAR(i);
            for (j = 0; j < 8u; ++j) {
                Busy_eep();
                BUSY_LCD();
                WriteDataXLCD(Read_b_eep(x+j));
            }
        }

        // Set the default messages
        for (i = 0; i < 4u; ++i) {
            BUSY_LCD();
            LCDGoto(1, i+1);
            x = EEP_LINE(i);
            for (j = 0; j < 20u; ++j) {
                Busy_eep();
                BUSY_LCD();
                WriteDataXLCD(Read_b_eep(x+j));
            }
        }

        // Start the timers / counters
        counter = 250;
        if (onFor) {
            secsx = 0;
            INTCONbits.GIE = 1;
        }
        powered_down = FALSE;
    }

    // Update backlight and contrast
    BL = PWM_ADVANCE(backlight);
    CT = PWM_ADVANCE(contrast);

    // Update GPOs
    if (gpo[0]) OUT1 = PWM_ADVANCE(gpo_pwm[0]);
    if (gpo[1]) OUT2 = PWM_ADVANCE(gpo_pwm[1]);
    if (gpo[2]) OUT3 = PWM_ADVANCE(gpo_pwm[2]);
    if (gpo[3]) OUT4 = PWM_ADVANCE(gpo_pwm[3]);
    if (gpo[4]) OUT5 = PWM_ADVANCE(gpo_pwm[4]);

    if (resetting) { // update count down timer
        if (secsx > 0u) {
            secsx = 0;
            BUSY_LCD();
            LCDGoto(14, 1);
            BUSY_LCD();
            WriteDataXLCD(--onFor + '0');
        }
        return;
    }

    // Possibly turn off display
    if (secsx >= 43u) { // 1 minute has passed
        secsx = 0;
        if (onFor == 1u) { // turn off display
            DCB_state.display = 0;
            BUSY_LCD();
            WriteCmdXLCD(DCB_state.bits);
            INTCONbits.GIE = 0; // we don't need to be timing anymore
        }
        if (onFor)
            onFor -= 1;
    }

    if (usb_device_state >= CONFIGURED_STATE) {
        // If we are configured we can communicate over USB, so we can send button states and receive commands

        // Check buttons (only every 25th time)
        if (++counter > 25u) {
            byte is = CUR_ROTARY(), was = PREV_ROTARY();
            if (was != is) {
                if (was == 0b10u && is == 0b00u || was == 0b00u && is == 0b01u || was == 0b01u && is == 0b11u || was == 0b11u && is == 0b10u) {
                    last_rotation = 'R';
                    put('R');
                } else if (was == 0b11u && is == 0b01u || was == 0b01u && is == 0b00u || was == 0b00u && is == 0b10u || was == 0b10u && is == 0b11u) {
                    last_rotation = 'L';
                    put('L');
                } else { // repeat last rotation
                    put(last_rotation);
                }
            }
            CHECK_BUTTON(1,'A');
            CHECK_BUTTON(2,'B');
            CHECK_BUTTON(3,'C');
            CHECK_BUTTON(4,'D');
            CHECK_BUTTON(5,'E');
            counter = 0;
        }
    
        // flush output buffer if we can
        if (mUSBUSARTIsTxTrfReady()) {
            mUSBUSARTTxRam(output_buffer,output_buffer_pos);
            output_buffer_pos = 0;
        }
    
        // check the lcd if its ready and get the next byte and work with it
        if (!BusyXLCD() && getNextByte()) {
            doCommand();
        }
    }

}//end ProcessIO

// Sets the cur_byte to the next byte and updates the input buffer
// If necessary it reads in a new input buffer from the serial port
// Returns TRUE if the cur_byte was updated, FALSE if there is no data at this time
BOOL getNextByte(void) {
    if (input_buffer_size <= input_buffer_pos) {
        //we are at the end of the buffer so we need to fill it up
        if (!getsUSBUSART(input_buffer,BUFFER_LEN)) { return FALSE; } //couldn't get any chars
        input_buffer_size = mCDCGetRxLength();
        input_buffer_pos = 0;
    }
    cur_byte = input_buffer[input_buffer_pos++];
    return TRUE;
}

void doCommand(void) {
    switch (next_cmd) {
    case NONE:			if (cur_byte==254u) { next_cmd = CMD; } else { WriteDataXLCD(cur_byte); } break;
    case CMD:			doCommand2(); break;
    //case DISCARD:		next_cmd = NONE; break;
    //case DISCARD_2: 	next_cmd = DISCARD; break;

    case POS_COL:		saved_byte = cur_byte; next_cmd = POS_ROW; break;
    case POS_ROW:		LCDGoto(saved_byte,cur_byte); next_cmd = NONE; break;

    case CUST_C:		WriteCmdXLCD(LCD_CUST_CHAR(cur_byte)); saved_byte = 0; next_cmd = CUST_X; break;
    case CUST_X:		WriteDataXLCD(cur_byte); if (++saved_byte >= 8u) { next_cmd = NONE; } break;

    case DISPLAY:		RememberIt(EEP_DISPLAY_MIN, onFor = cur_byte); secsx = 0; INTCONbits.GIE = onFor ? 1 : 0; next_cmd = NONE; break;
    case BACKLIGHT:		RememberIt(EEP_BACKLIGHT, cur_byte); setPWM(cur_byte, &backlight); next_cmd = NONE; break;
    case CONTRAST:		RememberIt(EEP_CONTRAST, cur_byte); setPWM((255-cur_byte)/2, &contrast); next_cmd = NONE; break;

    case GPO_OFF:		saved_byte = cur_byte-1; gpo[saved_byte] = FALSE; refreshGPO(saved_byte); next_cmd = NONE; break;
    case GPO_ON:		saved_byte = cur_byte-1; gpo[saved_byte] = TRUE; refreshGPO(saved_byte); next_cmd = NONE; break;
    case GPO_PWM_IND:	saved_byte = cur_byte-1; next_cmd = GPO_PWM; break;
    case GPO_PWM:		setPWM(cur_byte, gpo_pwm+saved_byte); refreshGPO(saved_byte); next_cmd = NONE; break;

    case READ_BUT:		DO_PRESSED(1,'A') else DO_PRESSED(2,'B') else DO_PRESSED(3,'C') else DO_PRESSED(4,'D') else DO_PRESSED(5,'E') next_cmd = NONE; break;

    case REMEMBER:		remember = cur_byte==1u; next_cmd = NONE; break;
    case REM_CUST_C:	saved_byte = cur_byte; next_cmd = REM_CUST_1; break;
    case REM_CUST_1: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,0), cur_byte); next_cmd = REM_CUST_2; break;
    case REM_CUST_2: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,1), cur_byte); next_cmd = REM_CUST_3; break;
    case REM_CUST_3: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,2), cur_byte); next_cmd = REM_CUST_4; break;
    case REM_CUST_4: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,3), cur_byte); next_cmd = REM_CUST_5; break;
    case REM_CUST_5: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,4), cur_byte); next_cmd = REM_CUST_6; break;
    case REM_CUST_6: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,5), cur_byte); next_cmd = REM_CUST_7; break;
    case REM_CUST_7: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,6), cur_byte); next_cmd = REM_CUST_8; break;
    case REM_CUST_8: 	Busy_eep(); Write_b_eep(EEP_CHAR_B(saved_byte,7), cur_byte); next_cmd = NONE; break;
    case REM_BCKLGHT:	Busy_eep(); Write_b_eep(EEP_BACKLIGHT, cur_byte); setPWM(cur_byte, &backlight); next_cmd = NONE; break;
    case REM_STARTUP:	Busy_eep(); Write_b_eep(EEP_MSG(0, saved_byte), cur_byte); if (++saved_byte >= 80u) { next_cmd = NONE; } break;
    case REM_GPO_IND:	saved_byte = cur_byte-1; next_cmd = REM_GPO_PWM; break;
    case REM_GPO_PWM:	Busy_eep(); Write_b_eep(EEP_GPO_PWM(saved_byte), cur_byte); next_cmd = NONE; break;
    case REM_GPO:		saved_byte = cur_byte-1; next_cmd = REM_GPO_ON; break;
    case REM_GPO_ON:	Busy_eep(); Write_b_eep(EEP_GPO(saved_byte), cur_byte > 0u); next_cmd = NONE; break;

    case READ_C_CUST:	WriteCmdXLCD(LCD_CUST_CHAR(cur_byte)); lcd2out(8); next_cmd = NONE; break;
    case READ_S_CUST:	cur_byte = EEP_CHAR(cur_byte); eeprom2out(cur_byte, cur_byte+8); next_cmd = NONE; break;

    case READ_C_GPO:	put(gpo[cur_byte-1]); next_cmd = NONE; break;
    case READ_C_GPOP:	put(PWM_VALUE(gpo_pwm[cur_byte-1])); next_cmd = NONE; break;
    case READ_S_GPO:	put(Read_b_eep(EEP_GPO(cur_byte-1)) > 0u); next_cmd = NONE; break;
    case READ_S_GPOP:	put(Read_b_eep(EEP_GPO_PWM(cur_byte-1))); next_cmd = NONE; break;

    case SER_NUM_1:		Busy_eep(); Write_b_eep(EEP_SER_NUM_0, cur_byte); next_cmd = SER_NUM_2; break;
    case SER_NUM_2:		Busy_eep(); Write_b_eep(EEP_SER_NUM_1, cur_byte); next_cmd = NONE; break;
    }
}

#define READ_MSG(r) LCDGoto(1, r); lcd2out(20);

void doCommand2(void) {
    switch (cur_byte) {
    case DisplayOn: 	DCB_state.display = 1;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = DISPLAY; break;
    case DisplayOff:	DCB_state.display = 0;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = NONE; onFor = 0; INTCONbits.GIE = 0; break;
    case CursorOn:		DCB_state.cursor = 1;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = NONE; break;
    case CursorOff:		DCB_state.cursor = 0;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = NONE; break;
    case BlinkOn:		DCB_state.blink = 1;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = NONE; break;
    case BlinkOff:		DCB_state.blink = 0;	RememberIt(EEP_DISPLAY, DCB_state.bits); WriteCmdXLCD(DCB_state.bits); next_cmd = NONE; break;
    case ClearDisplay:	WriteCmdXLCD(LCD_CLEAR);	 next_cmd = NONE; break;
    case Home:			WriteCmdXLCD(LCD_HOME);		 next_cmd = NONE; break;
    case CursorLeft:	WriteCmdXLCD(LCD_CUR_LEFT);	 next_cmd = NONE; break;
    case CursorRight:	WriteCmdXLCD(LCD_CUR_RIGHT); next_cmd = NONE; break;
    case Position: 		next_cmd = POS_COL; break;
    case Contrast: 		next_cmd = CONTRAST; break;
    case Backlight_:	
    case Backlight:		next_cmd = BACKLIGHT; break;
    case SaveBacklight:	next_cmd = REM_BCKLGHT; break;
    case DefineCustom:	next_cmd = CUST_C; break;
    case GPOoff:		next_cmd = GPO_OFF; break;
    case GPOon:			next_cmd = GPO_ON; break;
    case GPOpwm_:
    case GPOpwm:		next_cmd = GPO_PWM_IND; break;
    case RememberGPOpwm:next_cmd = REM_GPO_IND; break;
    case RememberGPO:	next_cmd = REM_GPO; break;
    case Remember:		next_cmd = REMEMBER; break;
    case RememberCustom:next_cmd = REM_CUST_C; break;
    case SaveStartup:	saved_byte = 0; next_cmd = REM_STARTUP; break;
    case ReadButton:	next_cmd = READ_BUT; break;

    case SetSerialNum:	next_cmd = SER_NUM_1; break;
    case ReadSerialNum: Busy_eep(); put(Read_b_eep(EEP_SER_NUM_0)); put(Read_b_eep(EEP_SER_NUM_1)); next_cmd = NONE; break;
    case ReadVersion:	put(VERSION); next_cmd = NONE; break;
    case ReadModuleType:put(MODULE);  next_cmd = NONE; break;

    case ReadDisplay:	put(DCB_state.bits);			next_cmd = NONE; break;
    case ReadDisplayMin:put(onFor);						next_cmd = NONE; break;
    case ReadContrast:	put(~(2*PWM_VALUE(contrast)));	next_cmd = NONE; break;
    case ReadBacklight:	put(PWM_VALUE(backlight));		next_cmd = NONE; break;
    case ReadCustom:	next_cmd = READ_C_CUST; break;
    case ReadMessage:	READ_MSG(1); BUSY_LCD(); READ_MSG(2); BUSY_LCD(); READ_MSG(3); BUSY_LCD(); READ_MSG(4); next_cmd = NONE;  break;
    case ReadGPO:		next_cmd = READ_C_GPO; break;
    case ReadGPOpwm:	next_cmd = READ_C_GPOP; break;

    case ReadSavedDisplay:		Busy_eep(); put(Read_b_eep(EEP_DISPLAY));		next_cmd = NONE; break;
    case ReadSavedDisplayMin:	Busy_eep(); put(Read_b_eep(EEP_DISPLAY_MIN));	next_cmd = NONE; break;
    case ReadSavedContrast:		Busy_eep(); put(Read_b_eep(EEP_CONTRAST));		next_cmd = NONE; break;
    case ReadSavedBacklight:	Busy_eep(); put(Read_b_eep(EEP_BACKLIGHT));		next_cmd = NONE; break;
    case ReadSavedCustom:		next_cmd = READ_S_CUST; break;
    case ReadSavedMessage:		Busy_eep(); eeprom2out(EEP_MSG_START, EEP_MSG_START+80); next_cmd = NONE;  break;
    case ReadSavedGPO:			next_cmd = READ_S_GPO; break;
    case ReadSavedGPOpwm:		next_cmd = READ_S_GPOP; break;

    case Char254:		WriteDataXLCD(254);

    //case PORDevice:		resetInit(); next_cmd = NONE; break;
    case Firmware:		firmwareReprogramInit(); next_cmd = NONE; break;

    default: next_cmd = NONE; break;
    }
}

// Go to a specific column and row in the LCD.
// Both start at 1 not 0.
void LCDGoto(byte col, byte row) {
    byte cmd;
    switch (row){
    case 1 : cmd = 0b10000000; break; //0
    case 2 : cmd = 0b11000000; break; //64
    case 3 : cmd = 0b10010100; break; //20
    default: cmd = 0b11010100; break; //84
    }
    WriteCmdXLCD(cmd+(col-1));
}

// Refresh a GPO: turn it on or off based on a change to the pwm.
void refreshGPO(byte x) {
    switch (x) {
    case 0: OUT1 = gpo[0] && PWM_ADVANCE(gpo_pwm[0]); break;
    case 1: OUT2 = gpo[1] && PWM_ADVANCE(gpo_pwm[1]); break;
    case 2: OUT3 = gpo[2] && PWM_ADVANCE(gpo_pwm[2]); break;
    case 3: OUT4 = gpo[3] && PWM_ADVANCE(gpo_pwm[3]); break;
    case 4: OUT5 = gpo[4] && PWM_ADVANCE(gpo_pwm[4]); break;
    }
}

// Update a PWM structure that has reached the end of one of it's parts
// Should only be used from PWM_ADVANCE.
// Always returns TRUE.
BOOL updatePWM(pwm *x) {
    x->cur = 0;
    if (++x->cur_repeat >= x->parts[x->cur_part].repeat) {
        x->cur_repeat = 0;
        x->cur_part = !x->cur_part;
    }
    return TRUE;
}

// Set a pwm structure's value to x.
// Note: 0 and 1 both count as always off, and 254 and 255 both count as always on. So 1 and 254 are not exactly right, but this is necessary for LCD Smartie compatibility.
// 
void setPWM(byte x, pwm *p) {
    p->cur = p->cur_repeat = p->cur_part = 0; // reset the counters in the pwm
    if (x > 253u) { // always on
        p->parts[0].ones = p->parts[1].ones = p->parts[0].total = p->parts[1].total = p->parts[1].repeat = p->parts[1].total = 255;
    } else if (x < 2u) { // always off
        p->parts[0].ones = p->parts[1].ones = 0;
        p->parts[0].total = p->parts[1].total = p->parts[1].repeat = p->parts[1].total = 255;
    } else {
        if (x > 127u) { // only 1 zero in each part
            x = ~x; // 255 - x
            p->parts[1].ones = (p->parts[0].ones = 255/x) - 1;
            p->parts[1].total = p->parts[0].ones;
        } else { // only 1 one in each part
            p->parts[0].ones = p->parts[1].ones = 1;
            p->parts[1].total = 255/x;
        }
        p->parts[0].total = p->parts[1].total + 1;
        p->parts[1].repeat = x - (p->parts[0].repeat = (255-x*(p->parts[1].total))/(p->parts[0].total-p->parts[1].total));
        if (p->parts[0].repeat != 0u) {
            //repeat reduction:
            //creates a more even distribution in 50 of 252 cases (resulting in 9.5 better distribution on avg in those cases, and 3.5 better overall)
            // all possible values are 1 3 5 15 17 51 (technically 85 but won't show up)
#define IS_DIVISOR(d) !(p->parts[0].repeat % d || p->parts[1].repeat % d)
#define REDUCE_BY(d)  { p->parts[0].repeat /= d;  p->parts[1].repeat /= d; }
            if (IS_DIVISOR(3)) {
                if (IS_DIVISOR(51))		REDUCE_BY(51)
                else if(IS_DIVISOR(15))	REDUCE_BY(15)
                else					REDUCE_BY(3) 	}
            else if (IS_DIVISOR(17))	REDUCE_BY(17)
            else if (IS_DIVISOR(5))		REDUCE_BY(5)
#undef REDUCE_BY
#undef IS_DIVISOR
        } else {
            //handle the 0 repeat cases by replicating parts[1] to parts[0]
            p->parts[1].repeat = 255; // reduces the number of switches between 0 and 1 (and thus the number of calls to updatePWM())
            p->parts[0] = p->parts[1];
        }
    }
}

void reset(void) { Reset(); }

void resetInit(void) {
    const rom char *msg;
    unsigned int len, i;

    BUSY_LCD();
    WriteCmdXLCD(LCD_CLEAR);
    BUSY_LCD();
    WriteCmdXLCD(0b00001100); // display on, no cursor, no blink
    Busy_eep();
    setPWM(Read_b_eep(EEP_BACKLIGHT), &backlight);
    setPWM((255-Read_b_eep(EEP_CONTRAST))/2, &contrast);

    BUSY_LCD();
    LCDGoto(1, 1);
    msg = "Resetting in 3";
    len = 14;
    for (i = 0; i < len; i++) {
        BUSY_LCD();
        WriteDataXLCD(msg[i]);
    }

    BUSY_LCD();
    LCDGoto(1, 2);
    msg = "Do not unplug";
    len = 13;
    for (i = 0; i < len; i++) {
        BUSY_LCD();
        WriteDataXLCD(msg[i]);
    }

    onFor = 4;
    secsx = 0;
    INTCONbits.GIE = 1;
    resetting = TRUE;
}

void firmwareReprogramInit(void) {
    Busy_eep();
    Write_b_eep(EEP_FIRMWARE, 0xFF);
    resetInit();
}

/** EOF user.c ***************************************************************/

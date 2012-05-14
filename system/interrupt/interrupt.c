/******************************************************************************
* PIC USB
* interrupt.c
******************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system/typedefs.h"
#include "system/interrupt/interrupt.h"

/** V A R I A B L E S ********************************************************/
extern byte secsx; // from user.c

/** I N T E R R U P T  V E C T O R S *****************************************/

#pragma code high_vector=0x808
void high_interrupt(void)
{
    _asm goto high_isr _endasm
}
#pragma code

#pragma code low_vector=0x818
void low_interrupt(void)
{
    _asm goto low_isr _endasm
}
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma interrupt high_isr
void high_isr(void)
{
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        ++secsx;
    } else {
        INTCON = 0; // panic! wont be able to disable the interrupt flag
    }
}

#pragma interruptlow low_isr
void low_isr(void)
{
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        ++secsx;
    } else {
        INTCON = 0; // panic! wont be able to disable the interrupt flag
    }
}
#pragma code

/** EOF interrupt.c **********************************************************/

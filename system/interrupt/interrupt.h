/******************************************************************************
* PIC USB
* interrupt.h
******************************************************************************/

#ifndef INTERRUPT_H
#define INTERRUPT_H

/** I N C L U D E S **********************************************************/

/** D E F I N I T I O N S ****************************************************/
#define mEnableInterrupt()          INTCONbits.GIE = 1;


/** S T R U C T U R E S ******************************************************/

/** E X T E R N S ************************************************************/

/** P R O T O T Y P E S ******************************************************/
void low_isr(void);
void high_isr(void);

#endif //INTERRUPT_H





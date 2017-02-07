//
//  timer.c
//  
//
//  Created by Matthew Fonken on 2/7/17.
//
//

#include "timer.h"

void TMR_Init( U8 psa, U8 value )
{
    /* Prescaler value - See p145 of datasheet */
    OPTION_REG = 0xC0 | psa;
    TMR0 = 0xFF - value; //Timer0 module register
    TMR0IE = 1;
    ei(); //Enable all configured interrupts
}

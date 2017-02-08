#include "types.h"
#include "config_bits.h"
#include "config.h"
#include "timer.h"
#include "radio.h"
#include "si4355.h"
#include "spi.h"

states STATE = STARTUP;
int counter = 0;

void main( void )
{
    SPI_Init();
    while(1)
    {
        switch( STATE )
        {
            case STARTUP:
                Radio_Init();
            case ARMED:
                Radio_StartRX( 0u );
                /* Reset RX FIFO */
                si4355_fifo_info( 0x02 );
                STATE = RECEIVING;
                break;
            case RECEIVING:
                if( Radio_CheckReceived() );
                STATE = ARMED;
                break;
            default:
                STATE = ARMED;
        }
    }
    return;
}

void interrupt Timer0_ISR( void )
{
    TMR0IF = 0;         //Clear the timer interrupt flag
    counter++;
    RA0 = counter & 1;  //Toggle the LED
}

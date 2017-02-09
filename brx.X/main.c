#include "types.h"
#include "config_bits.h"
#include "config.h"
#include "timer.h"
#include "radio.h"
#include "si4355.h"
#include "spi.h"

states STATE = STARTUP;
int counter = 0;

#define LED0     0x00 
#define SCK0     0x01 
#define SDI0     0x02 
#define SDO0     0x04 
#define SS0      0x05 


 
void main( void )
{
    HW_Config();
    SPI_Init();
    U8 wait = 100;
    for(; wait != 0; wait--);
    U8 r = 0;
    while(!r)
    {
        SS_PIN = 0;
        SPI_WriteByte(0x44);
        r = SPI_ReadByte();
        SS_PIN = 1;
    }
    while(1);
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

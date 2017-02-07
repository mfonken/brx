#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "config_bits.h"
#include "spi.h"



#define LED     0x00
#define SCK     0x01
#define SDI     0x02
#define SDO     0x04
#define SS      0x05

#define     _XTAL_FREQ 1000000  

int counter = 0;

void TMR_Init( void )
{
    OPTION_REG = 0xC7; //Set prescaler to 256
    TMR0 = 0xFF; //Timer0 module register
    TMR0IE = 1;
    ei(); //Enable all configured interrupts
}

void main( void )
{
    TRISA = ~( ( 1 << LED ) | ( 1 << SCK) | ( 1 << SDO ) | ( 1 << SS ) ); 
    RA5 = 1;
    SPI_Init();	
    TMR_Init();
    __delay_ms(10);
    RA5 = 0;
    SPI_Write(0x44);
    SPI_Read();
    SPI_Write(0x02);
    SPI_Write(0x01);
    SPI_Write(0x00);
    SPI_Write(0x01);
    SPI_Write(0xC9);
    SPI_Write(0xC3);
    SPI_Write(0x80);
    SPI_Read();
//    SPI_Write(0x20);
//    SPI_Write(0x00);
//    SPI_Write(0x00);
//    SPI_Write(0x00);
//    SPI_Read();
    RA5 = 1;
    
    while (1); //Loop forever

    return;
}

void interrupt Timer0_ISR(void)
{
    TMR0IF = 0;         //Clear the timer interrupt flag
    counter++;
    RA0 = counter & 1;  //Toggle the LED
    U8 c = 8;
    if( counter & 1)
    {
        RA5 = 0;
        SPI_Write(0x01);
        SPI_Write(0x00);
        SPI_Write(0x00);
        SPI_Write(0x00);

        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        SPI_Read();
        
        RA5 = 1;
    }
    counter &= 0xFF;
}
#include "spi.h"

U8 dummy;

void SPI_Init( void ) 
{    
    /* Disable SSP */
    SSPEN   = 0;
    /* Set alternate pins locations */
    SDOSEL  = 1;
    SSSEL   = 0;
    /* SPI Data Input Sample Bit Reset */
	SMP     = 0;
    /* SPI Clock Edge - Idle to active */
	CKE     = 0;
    /* Idle clock on low */
	CKP     = 0;
    /* SS Mode - SPI Fosc/4 */
	SSPM0   = 0;
    SSPM1   = 0;
    SSPM2   = 0;
    SSPM3   = 0;
    
    //SSP1IE  = 1;
    /* Enable SSP */
	SSPEN   = 1;
} 

void SPI_Write(unsigned char data)
{   
    SSPBUF = data; 
    while (!SSP1IF);  //wait for transmission complete 
    data = SSPBUF; 
}

unsigned char SPI_Read( void )
{   
    unsigned char data;
	SSPBUF = 0;				// write out to buffer
    while(!BF);				// wait for flag
    data = SSPBUF;
    return data;
}
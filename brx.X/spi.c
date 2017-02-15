#include "spi.h"
#include "config.h"
#define SPI_WAIT_TIME 0
U8 wait;
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
	SSPM0   = 1;
    SSPM1   = 0;
    SSPM2   = 0;
    SSPM3   = 0;

    SSP1IE  = 1;
    /* Enable SSP */
	SSPEN   = 1;
} 

void SPI_WriteBytes( U8 len, U8 * data )
{
    while( len-- )
    {
        SPI_WriteByte( *data++ );
    }
}
#define nop() {_asm nop _endasm}
void SPI_WriteByte( U8 data )
{   
    SSPBUF = data; 
    while( !SSP1IF );
    data = SSPBUF;
    wait = SPI_WAIT_TIME;
    while(wait--);
}

void SPI_ReadBytes( U8 len, U8 * data )
{
    while( len-- )
    {
        *data++ = SPI_ReadByte();
    }
}

U8 SPI_ReadByte( void )
{   
    register U8 data = 0;
	SSPBUF = 0;				// write out to buffer
    while( BF == 0 );				// wait for flag
    data = SSPBUF;
    wait = SPI_WAIT_TIME;
    while(wait--);
    return data;
}

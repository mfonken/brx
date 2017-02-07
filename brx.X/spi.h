/* 
 * File:   spi.h
 */

#ifndef SPI_H
#define	SPI_H

#include "types.h"

void SPI_Init( void );
void SPI_Write(unsigned char data);
unsigned char SPI_Read( void );

#endif	/* SPI_H */

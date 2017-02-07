/* 
 * File:   spi.h
 */

#ifndef SPI_H
#define	SPI_H

#include <xc.h>
#include "types.h"

#ifdef	__cplusplus
extern "C" {
#endif

void SPI_Init( void );
void SPI_Write(unsigned char data);
unsigned char SPI_Read( void );

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */
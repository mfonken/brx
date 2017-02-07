#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

// PIN CONFIGURATION

#define LED     RA0
#define SCK     RA1
#define SDI     RA2
#define IRQ     RA3
#define SDO     RA4
#define SS      RA5
    
extern states STATE;

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

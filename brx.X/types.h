#ifndef TYPES_H
#define	TYPES_H

#include <xc.h>
#include <stdint.h>

typedef unsigned char U8;
typedef unsigned char U8;
typedef unsigned int  U16;
typedef unsigned long U32;

typedef bool BIT;

typedef enum
{
    STARTUP,
    ARMED,
    RECEIVING,
} states;

#endif	/* TYPES_H */


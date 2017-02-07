#ifndef _RADIO_HAL_H_
#define _RADIO_HAL_H_

BIT  radio_hal_Gpio0Level(void);
BIT  radio_hal_Gpio1Level(void);
BIT  radio_hal_Gpio2Level(void);
BIT  radio_hal_Gpio3Level(void);
BIT  radio_hal_NirqLevel(void);
void radio_hal_AssertShutdown(void);
void radio_hal_DeassertShutdown(void);
void radio_hal_ClearNsel(void);
void radio_hal_SetNsel(void);
void radio_hal_SpiWriteByte(U8 byteToWrite);
U8   radio_hal_SpiReadByte(void);
void radio_hal_SpiWriteData(U8 byteCount, U8* pData);
void radio_hal_SpiReadData(U8 byteCount, U8* pData);

#endif //_RADIO_HAL_H_

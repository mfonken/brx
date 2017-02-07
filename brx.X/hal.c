#include "types.h"
#include "../C8051F930_defs.h"
#include "../hardware_defs.h"
#include "../spi_wrapper.h"
#include "hal.h"

BIT radio_hal_Gpio0Level(void)
{
    #ifdef SILABS_PLATFORM_DKMB
    return 0;
    #endif
    #ifdef SILABS_PLATFORM_UDP
    return EZRP_RX_DOUT;
    #endif
    #ifdef SILABS_PLATFORM_RFSTICK
    return RF_GPIO0;
    #endif
}

BIT radio_hal_Gpio1Level(void)
{
    #ifdef SILABS_PLATFORM_DKMB
    return FSK_CLK_OUT;
    #endif
    #ifdef SILABS_PLATFORM_UDP
    return 0; //No Pop
    #endif
    #ifdef SILABS_PLATFORM_RFSTICK
    return RF_GPIO1;
    #endif
}

BIT radio_hal_Gpio2Level(void)
{
    #ifdef SILABS_PLATFORM_DKMB
    return DATA_NFFS;
    #endif
    #ifdef SILABS_PLATFORM_UDP
    return 0; //No Pop
    #endif
    #ifdef SILABS_PLATFORM_RFSTICK
    return RF_GPIO2;
    #endif
}

BIT radio_hal_Gpio3Level(void)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    return RF_GPIO3;
    #else
    return 0;
    #endif
}

BIT radio_hal_NirqLevel(void)
{
    return RF_NIRQ;
}

void radio_hal_AssertShutdown(void)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    RF_PWRDN = 1;
    #else
    PWRDN = 1;
    #endif
}

void radio_hal_DeassertShutdown(void)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    RF_PWRDN = 0;
    #else
    PWRDN = 0;
    #endif
}

void radio_hal_ClearNsel(void)
{
    RF_NSEL = 0;
}

void radio_hal_SetNsel(void)
{
    RF_NSEL = 1;
}

void radio_hal_SpiWriteByte(U8 byteToWrite)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    bSpi_ReadWriteSpi1(byteToWrite);
    #else
    SpiReadWrite(byteToWrite);
    #endif
}

U8 radio_hal_SpiReadByte(void)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    return bSpi_ReadWriteSpi1(0xFF);
    #else
    return SpiReadWrite(0xFF);
    #endif
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    vSpi_WriteDataSpi1(byteCount, pData);
    #else
    SpiWriteData(byteCount, pData);
    #endif
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
    #ifdef SILABS_PLATFORM_RFSTICK
    vSpi_ReadDataSpi1(byteCount, pData);
    #else
    SpiReadData(byteCount, pData);
    #endif
}

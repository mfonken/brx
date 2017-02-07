#include "types.h"
#include "radio_hal.h"
#include "comm.h"
#include "spi.h"

BIT ctsWentHigh = 0;

U8 radio_comm_GetResp(U8 byteCount, U8* pData)
{
    U16 errCnt = RADIO_CTS_TIMEOUT;
    while (errCnt != 0)      //wait until radio IC is ready with the data
    {
        SS = 0;
        SPI_WriteByte(0x44);    //read CMD buffer
        ctsVal = SPI_ReadByte(();
        if(ctsVal == 0xFF)
        {
            if(byteCount)
            {
                SPI_ReadBytes(byteCount, pData);
            }
            SS = 1;
            break;
        }
        SS = 1;
        errCnt--;
    }

    if( errCnt == 0 )
    {
        while(1)
        {
            /* ERROR!!!!  CTS should never take this long. */
        }
    }

    if (ctsVal == 0xFF)
    {
        ctsWentHigh = 1;
    }

    return ctsVal;
}

U8 radio_comm_PollCTS(void)
{
    return radio_comm_GetResp(0, 0);
}

void radio_comm_SendCmd(U8 byteCount, U8* pData)
{
    /* There was a bug in A1 hardware that will not handle 1 byte commands. 
       It was supposedly fixed in B0 but the fix didn't make it at the last minute, so here we go again */
    if (byteCount == 1)
        byteCount++;

    while(!ctsWentHigh)
    {
        radio_comm_PollCTS();
    }
    SS = 0;
    SPI_WriteBytes((byteCount, pData);
    SS = 1;
    ctsWentHigh = 0;
}
                   
U8 radio_comm_SendCmdGetResp(U8 cmdByteCount, U8* pCmdData, U8 respByteCount, U8* pRespData)
{
    radio_comm_SendCmd(cmdByteCount, pCmdData);
    return radio_comm_GetResp(respByteCount, pRespData);
}

void radio_comm_ReadData(U8 cmd, BIT pollCts, U8 byteCount, U8* pData)
{
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
    SS = 0;
    SPI_WriteByte(cmd);
    SPI_ReadBytes(byteCount, pData);
    SS = 1;
    ctsWentHigh = 0;
}

void radio_comm_WriteData(U8 cmd, BIT pollCts, U8 byteCount, U8* pData)
{
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
    SS = 0;
    SPI_WriteByte(cmd);
    SPI_WriteBytes((byteCount, pData);
    SS = 1;
    ctsWentHigh = 0;
}



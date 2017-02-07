#ifndef _RADIO_COMM_H_
#define _RADIO_COMM_H_

//#define RADIO_CTS_TIMEOUT 255
#define RADIO_CTS_TIMEOUT 5000

extern SEGMENT_VARIABLE(radioCmd[16u], U8, SEG_XDATA);

U8 radio_comm_GetResp(U8 byteCount, U8* pData);
U8 radio_comm_PollCTS(void);
void radio_comm_SendCmd(U8 byteCount, U8* pData);
U8 radio_comm_SendCmdGetResp(U8 cmdByteCount, U8* pCmdData, U8 respByteCount, U8* pRespData);
void radio_comm_ReadData(U8 cmd, BIT pollCts, U8 byteCount, U8* pData);
void radio_comm_WriteData(U8 cmd, BIT pollCts, U8 byteCount, U8* pData);

#endif //_RADIO_COMM_H_

#include <stdarg.h>
#include "si4355_defs.h"
#include "si4355h"

#define SI4355_XTAL_FREQ 30000000L

union si4355_cmd_reply_union Si4355Cmd;
U8 radioCmd[16u];

void si4355_reset(void)
{
    /* No access to SDN pin */
    /* ? try software reset ? */
}


void si4355_nop(void)
{
    radioCmd[0] = SI4355_CMD_ID_NOP;

    radio_comm_SendCmd( SI4355_CMD_ARG_COUNT_NOP, radioCmd );
}


void si4355_part_info(void)
{
    radioCmd[0] = SI4355_CMD_ID_PART_INFO;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_PART_INFO,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_PART_INFO,
                              radioCmd );

    Si4355Cmd.PART_INFO.CHIPREV         = radioCmd[0];
    Si4355Cmd.PART_INFO.PART.U8[MSB]    = radioCmd[1];
    Si4355Cmd.PART_INFO.PART.U8[LSB]    = radioCmd[2];
    Si4355Cmd.PART_INFO.PBUILD          = radioCmd[3];
    Si4355Cmd.PART_INFO.ID.U8[MSB]      = radioCmd[4];
    Si4355Cmd.PART_INFO.ID.U8[LSB]      = radioCmd[5];
    Si4355Cmd.PART_INFO.CUSTOMER        = radioCmd[6];
    Si4355Cmd.PART_INFO.ROMID           = radioCmd[7];
    Si4355Cmd.PART_INFO.BOND            = radioCmd[8];
}


void si4355_power_up(U8 BOOT_OPTIONS, U8 XTAL_OPTIONS, U32 XO_FREQ)
{
    radioCmd[0] = SI4355_CMD_ID_POWER_UP;
    radioCmd[1] = BOOT_OPTIONS;
    radioCmd[2] = XTAL_OPTIONS;
    radioCmd[3] = (U8)(XO_FREQ >> 24);
    radioCmd[4] = (U8)(XO_FREQ >> 16);
    radioCmd[5] = (U8)(XO_FREQ >> 8);
    radioCmd[6] = (U8)(XO_FREQ);

    radio_comm_SendCmd( SI4355_CMD_ARG_COUNT_POWER_UP, radioCmd );
}


void si4355_func_info(void)
{
    radioCmd[0] = SI4355_CMD_ID_FUNC_INFO;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_FUNC_INFO,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_FUNC_INFO,
                              radioCmd );

    Si4355Cmd.FUNC_INFO.REVEXT          = radioCmd[0];
    Si4355Cmd.FUNC_INFO.REVBRANCH       = radioCmd[1];
    Si4355Cmd.FUNC_INFO.REVINT          = radioCmd[2];
    Si4355Cmd.FUNC_INFO.PATCH.U8[MSB]   = radioCmd[3];
    Si4355Cmd.FUNC_INFO.PATCH.U8[LSB]   = radioCmd[4];
    Si4355Cmd.FUNC_INFO.FUNC            = radioCmd[5];
    Si4355Cmd.FUNC_INFO.SVNFLAGS        = radioCmd[6];
    Si4355Cmd.FUNC_INFO.SVNREV.U8[b3]   = radioCmd[7];
    Si4355Cmd.FUNC_INFO.SVNREV.U8[b2]   = radioCmd[8];
    Si4355Cmd.FUNC_INFO.SVNREV.U8[b1]   = radioCmd[9];
    Si4355Cmd.FUNC_INFO.SVNREV.U8[b0]   = radioCmd[10];
}

#ifdef __C51__
#pragma maxargs (13)  /* allow 13 bytes for parameters */
#endif
void si4355_set_property( U8 GROUP, U8 NUM_PROPS, U8 START_PROP, ... )
{
    va_list argList;
    U8 cmdIndex;

    radioCmd[0] = SI4355_CMD_ID_SET_PROPERTY;
    radioCmd[1] = GROUP;
    radioCmd[2] = NUM_PROPS;
    radioCmd[3] = START_PROP;

    va_start (argList, START_PROP);
    cmdIndex = 4;
    while(NUM_PROPS--)
    {
        radioCmd[cmdIndex] = va_arg (argList, U8);
        cmdIndex++;
    }
    va_end(argList);

    radio_comm_SendCmd( cmdIndex, radioCmd );
}


void si4355_get_property(U8 GROUP, U8 NUM_PROPS, U8 START_PROP)
{
    radioCmd[0] = SI4355_CMD_ID_GET_PROPERTY;
    radioCmd[1] = GROUP;
    radioCmd[2] = NUM_PROPS;
    radioCmd[3] = START_PROP;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_GET_PROPERTY,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_GET_PROPERTY,
                              radioCmd );

    Si4355Cmd.GET_PROPERTY.DATA0    = radioCmd[0];
    Si4355Cmd.GET_PROPERTY.DATA1    = radioCmd[1];
    Si4355Cmd.GET_PROPERTY.DATA2    = radioCmd[2];
    Si4355Cmd.GET_PROPERTY.DATA3    = radioCmd[3];
    Si4355Cmd.GET_PROPERTY.DATA4    = radioCmd[4];
    Si4355Cmd.GET_PROPERTY.DATA5    = radioCmd[5];
    Si4355Cmd.GET_PROPERTY.DATA6    = radioCmd[6];
    Si4355Cmd.GET_PROPERTY.DATA7    = radioCmd[7];
    Si4355Cmd.GET_PROPERTY.DATA8    = radioCmd[8];
    Si4355Cmd.GET_PROPERTY.DATA9    = radioCmd[9];
    Si4355Cmd.GET_PROPERTY.DATA10   = radioCmd[10];
    Si4355Cmd.GET_PROPERTY.DATA11   = radioCmd[11];
    Si4355Cmd.GET_PROPERTY.DATA12   = radioCmd[12];
    Si4355Cmd.GET_PROPERTY.DATA13   = radioCmd[13];
    Si4355Cmd.GET_PROPERTY.DATA14   = radioCmd[14];
    Si4355Cmd.GET_PROPERTY.DATA15   = radioCmd[15];
}


void si4355_gpio_pin_cfg(U8 GPIO0, U8 GPIO1, U8 GPIO2, U8 GPIO3, U8 NIRQ, U8 SDO, U8 GEN_CONFIG)
{
    radioCmd[0] = SI4355_CMD_ID_GPIO_PIN_CFG;
    radioCmd[1] = GPIO0;
    radioCmd[2] = GPIO1;
    radioCmd[3] = GPIO2;
    radioCmd[4] = GPIO3;
    radioCmd[5] = NIRQ;
    radioCmd[6] = SDO;
    radioCmd[7] = GEN_CONFIG;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_GPIO_PIN_CFG,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_GPIO_PIN_CFG,
                              radioCmd );

    Si4355Cmd.GPIO_PIN_CFG.GPIO0        = radioCmd[0];
    Si4355Cmd.GPIO_PIN_CFG.GPIO1        = radioCmd[1];
    Si4355Cmd.GPIO_PIN_CFG.GPIO2        = radioCmd[2];
    Si4355Cmd.GPIO_PIN_CFG.GPIO3        = radioCmd[3];
    Si4355Cmd.GPIO_PIN_CFG.NIRQ         = radioCmd[4];
    Si4355Cmd.GPIO_PIN_CFG.SDO          = radioCmd[5];
    Si4355Cmd.GPIO_PIN_CFG.GEN_CONFIG   = radioCmd[6];
}

void si4355_fifo_info(U8 FIFO)
{
    radioCmd[0] = SI4355_CMD_ID_FIFO_INFO;
    radioCmd[1] = FIFO;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_FIFO_INFO,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_FIFO_INFO,
                              radioCmd );

    Si4355Cmd.FIFO_INFO.RX_FIFO_COUNT   = radioCmd[0];
    Si4355Cmd.FIFO_INFO.TX_FIFO_SPACE   = radioCmd[1];
}

void si4355_write_ezconfig_array(U8 numBytes, U8* pEzConfigArray)
{
  radio_comm_WriteData(SI4355_CMD_ID_WRITE_TX_FIFO, 1, numBytes, pEzConfigArray);
}

void si4355_ezconfig_check(U16 CHECKSUM)
{
  /* Do not check CTS */

  SS = 0;

  /* Command byte */
  SPI_WriteByte(SI4355_CMD_ID_EZCONFIG_CHECK);

  /* CRC */
  SPI_WriteByte((U16) CHECKSUM >> 8u);
  SPI_WriteByte((U16) CHECKSUM & 0x00FF);

  SS = 1;

  /* Get the respoonse from the radio chip */
  radio_comm_GetResp(1u, radioCmd);
}


void si4355_get_int_status(U8 PH_CLR_PEND, U8 MODEM_CLR_PEND, U8 CHIP_CLR_PEND)
{
    radioCmd[0] = SI4355_CMD_ID_GET_INT_STATUS;
    radioCmd[1] = PH_CLR_PEND;
    radioCmd[2] = MODEM_CLR_PEND;
    radioCmd[3] = CHIP_CLR_PEND;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_GET_INT_STATUS,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_GET_INT_STATUS,
                              radioCmd );

    Si4355Cmd.GET_INT_STATUS.INT_PEND       = radioCmd[0];
    Si4355Cmd.GET_INT_STATUS.INT_STATUS     = radioCmd[1];
    Si4355Cmd.GET_INT_STATUS.PH_PEND        = radioCmd[2];
    Si4355Cmd.GET_INT_STATUS.PH_STATUS      = radioCmd[3];
    Si4355Cmd.GET_INT_STATUS.MODEM_PEND     = radioCmd[4];
    Si4355Cmd.GET_INT_STATUS.MODEM_STATUS   = radioCmd[5];
    Si4355Cmd.GET_INT_STATUS.CHIP_PEND      = radioCmd[6];
    Si4355Cmd.GET_INT_STATUS.CHIP_STATUS    = radioCmd[7];
}


void si4355_start_tx(U8 CHANNEL, U8 CONDITION, U16 TX_LEN)
{
    radioCmd[0] = SI4355_CMD_ID_START_TX;
    radioCmd[1] = CHANNEL;
    radioCmd[2] = CONDITION;
    radioCmd[3] = (U8)(TX_LEN >> 8);
    radioCmd[4] = (U8)(TX_LEN);

    radio_comm_SendCmd( SI4355_CMD_ARG_COUNT_START_TX, radioCmd );
}


void si4355_start_rx(U8 CHANNEL, U8 CONDITION, U16 RX_LEN, U8 NEXT_STATE1, U8 NEXT_STATE2, U8 NEXT_STATE3)
{
    radioCmd[0] = SI4355_CMD_ID_START_RX;
    radioCmd[1] = CHANNEL;
    radioCmd[2] = CONDITION;
    radioCmd[3] = (U8)(RX_LEN >> 8);
    radioCmd[4] = (U8)(RX_LEN);
    radioCmd[5] = NEXT_STATE1;
    radioCmd[6] = NEXT_STATE2;
    radioCmd[7] = NEXT_STATE3;

    radio_comm_SendCmd( SI4355_CMD_ARG_COUNT_START_RX, radioCmd );
}


void si4355_request_device_state(void)
{
    radioCmd[0] = SI4355_CMD_ID_REQUEST_DEVICE_STATE;

    radio_comm_SendCmdGetResp( SI4355_CMD_ARG_COUNT_REQUEST_DEVICE_STATE,
                              radioCmd,
                              SI4355_CMD_REPLY_COUNT_REQUEST_DEVICE_STATE,
                              radioCmd );

    Si4355Cmd.REQUEST_DEVICE_STATE.CURR_STATE       = radioCmd[0];
    Si4355Cmd.REQUEST_DEVICE_STATE.CURRENT_CHANNEL  = radioCmd[1];
}


void si4355_change_state(U8 NEXT_STATE1)
{
    radioCmd[0] = SI4355_CMD_ID_CHANGE_STATE;
    radioCmd[1] = NEXT_STATE1;

    radio_comm_SendCmd( SI4355_CMD_ARG_COUNT_CHANGE_STATE, radioCmd );
}


void si4355_read_cmd_buff(void)
{
    // TODO:
}


void si4355_frr_a_read(U8 respByteCount)
{
    radio_comm_ReadData(SI4355_CMD_ID_FRR_A_READ,
                            0,
                        respByteCount,
                        radioCmd);

    Si4355Cmd.FRR_A_READ.FRR_A_VALUE = radioCmd[0];
    Si4355Cmd.FRR_A_READ.FRR_B_VALUE = radioCmd[1];
    Si4355Cmd.FRR_A_READ.FRR_C_VALUE = radioCmd[2];
    Si4355Cmd.FRR_A_READ.FRR_D_VALUE = radioCmd[3];
}


void si4355_frr_b_read(U8 respByteCount)
{
    radio_comm_ReadData(SI4355_CMD_ID_FRR_B_READ,
                            0,
                        respByteCount,
                        radioCmd);

    Si4355Cmd.FRR_B_READ.FRR_B_VALUE = radioCmd[0];
    Si4355Cmd.FRR_B_READ.FRR_C_VALUE = radioCmd[1];
    Si4355Cmd.FRR_B_READ.FRR_D_VALUE = radioCmd[2];
    Si4355Cmd.FRR_B_READ.FRR_A_VALUE = radioCmd[3];
}


void si4355_frr_c_read(U8 respByteCount)
{
    radio_comm_ReadData(SI4355_CMD_ID_FRR_C_READ,
                            0,
                        respByteCount,
                        radioCmd);

    Si4355Cmd.FRR_C_READ.FRR_C_VALUE = radioCmd[0];
    Si4355Cmd.FRR_C_READ.FRR_D_VALUE = radioCmd[1];
    Si4355Cmd.FRR_C_READ.FRR_A_VALUE = radioCmd[2];
    Si4355Cmd.FRR_C_READ.FRR_B_VALUE = radioCmd[3];
}


void si4355_frr_d_read(U8 respByteCount)
{
    radio_comm_ReadData(SI4355_CMD_ID_FRR_D_READ,
                            0,
                        respByteCount,
                        radioCmd);

    Si4355Cmd.FRR_D_READ.FRR_D_VALUE = radioCmd[0];
    Si4355Cmd.FRR_D_READ.FRR_A_VALUE = radioCmd[1];
    Si4355Cmd.FRR_D_READ.FRR_B_VALUE = radioCmd[2];
    Si4355Cmd.FRR_D_READ.FRR_C_VALUE = radioCmd[3];
}


void si4355_write_tx_fifo(U8 numBytes, U8* pTxData)
{
    radio_comm_WriteData( SI4355_CMD_ID_WRITE_TX_FIFO, 0, numBytes, pTxData );
}

void si4355_read_rx_fifo(U8 numBytes, U8* pRxData)
{
    radio_comm_ReadData( SI4355_CMD_ID_READ_RX_FIFO, 0, numBytes, pRxData );
}

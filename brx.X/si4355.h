#ifndef _SI4355_H_
#define _SI4355_H_

extern union si4355_cmd_reply_union Si4355Cmd;
extern U8 radioCmd[16];

#define SI4355_FIFO_SIZE 64

enum
{
    SI4355_SUCCESS,
    SI4355_NO_PATCH,
    SI4355_CTS_TIMEOUT,
    SI4355_PATCH_FAIL,
    SI4355_COMMAND_ERROR
};


void si4355_reset(void);
void si4355_nop(void);
void si4355_part_info(void);
void si4355_power_up(U8 BOOT_OPTIONS, U8 XTAL_OPTIONS, U32 XO_FREQ);

void si4355_func_info(void);
void si4355_set_property( U8 GROUP, U8 NUM_PROPS, U8 START_PROP, ... );
void si4355_get_property(U8 GROUP, U8 NUM_PROPS, U8 START_PROP);
void si4355_gpio_pin_cfg(U8 GPIO0, U8 GPIO1, U8 GPIO2, U8 GPIO3, U8 NIRQ, U8 SDO, U8 GEN_CONFIG);
void si4355_fifo_info(U8 FIFO);
void si4355_write_ezconfig_array(U8 numBytes, U8* pEzConfigArray);
void si4355_ezconfig_check(U16 CHECKSUM);

void si4355_get_int_status(U8 PH_CLR_PEND, U8 MODEM_CLR_PEND, U8 CHIP_CLR_PEND);

void si4355_start_tx(U8 CHANNEL, U8 CONDITION, U16 TX_LEN);
void si4355_start_rx(U8 CHANNEL, U8 CONDITION, U16 RX_LEN, U8 NEXT_STATE1, U8 NEXT_STATE2, U8 NEXT_STATE3);
void si4355_request_device_state(void);
void si4355_change_state(U8 NEXT_STATE1);
void si4355_read_cmd_buff(void);
void si4355_frr_a_read(U8 respByteCount);
void si4355_frr_b_read(U8 respByteCount);
void si4355_frr_c_read(U8 respByteCount);
void si4355_frr_d_read(U8 respByteCount);

void si4355_write_tx_fifo( U8 numBytes, U8* pData );
void si4355_read_rx_fifo( U8 numBytes, U8* pRxData );

#endif //_SI4355_API_LIB_H_

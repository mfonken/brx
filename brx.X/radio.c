#include "types.h"
#include "radio.h"

/* Get configuration for config file */
#define RADIO_MULTIPLE_CONFIG_NO_3
#include "radio_config.h"
#define INIT_CONFIG( t ) tEzConfigArray t = EZCONFIG_ARRAY_DATA

tEzConfigArray config;

void Radio_PowerUp(void);
U8 bRadio_Check_Ezconfig(U16);

void Radio_PowerUp(void)
{
    U16 wDelay = 0u;
    
    si4355_reset();
    for (; wDelay < config->Radio_Delay_Cnt_After_Reset; wDelay++);
    
    si4355_power_up(config->Radio_BOOT_OPTIONS,
                    config->Radio_XTAL_OPTIONS,
                    config->Radio_XO_FREQ);
    
    radio_comm_PollCTS();
}

void Radio_Init(void)
{
    INIT_CONFIG( config );
    Radio_SetChip();
}

void Radio_SetChip()
{
    U8 lTemp;
    
    do
    {
        /* Power Up the radio chip */
        Radio_PowerUp();
        
        /* Load the 1st part of the configuration array (128 bytes) */
        si4355_write_ezconfig_array(128u, config->Radio_Configuration);
        /* Load the final part of the configuration array (128 bytes) */
        si4355_write_ezconfig_array(EZCONFIG_RADIO_CFG_SIZE - 128u, (U8 *) config->Radio_Configuration + 128u);
        
        lTemp = bRadio_Check_Ezconfig(config->Radio_Configuration_CRC);
        
    } while(lTemp != 0u);
    
    // Read ITs, clear pending ones
    si4355_get_int_status(0u, 0u, 0u);
    
    /* Enable ITs */
    si4355_set_property(
                        SI4355_PROP_GRP_ID_INT_CTL,
                        SI4355_PROP_GRP_LEN_INT_CTL,
                        SI4355_PROP_GRP_INDEX_INT_CTL_ENABLE,
                        (U8) config->Radio_INT_CTL_ENABLE,
                        (U8) config->Radio_INT_CTL_PH_ENABLE,
                        (U8) config->Radio_INT_CTL_MODEM_ENABLE,
                        (U8) config->Radio_INT_CTL_CHIP_ENABLE
                        );
    
    // Configure Fast response registers
    si4355_set_property(
                        SI4355_PROP_GRP_ID_FRR_CTL,
                        SI4355_PROP_GRP_LEN_FRR_CTL,
                        SI4355_PROP_GRP_INDEX_FRR_CTL_A_MODE,
                        (U8) config->Radio_FRR_CTL_A_MODE,
                        (U8) config->Radio_FRR_CTL_B_MODE,
                        (U8) config->Radio_FRR_CTL_C_MODE,
                        (U8) config->Radio_FRR_CTL_D_MODE
                        );
    
    // Configure GPIO pins
    si4355_gpio_pin_cfg(
                        (U8) config->Radio_GPIO0_PIN_CFG,
                        (U8) config->Radio_GPIO1_PIN_CFG,
                        (U8) config->Radio_GPIO2_PIN_CFG,
                        (U8) config->Radio_GPIO3_PIN_CFG,
                        (U8) config->Radio_GPIO_NIRQ_MODE,
                        (U8) config->Radio_GPIO_SDO_MODE,
                        (U8) config->Radio_GPIO_GEN_CONFIG
                        );
    
    // Put the Radio into SLEEP state
    si4355_change_state(config->Radio_Mode_After_Power_Up);
    
    // Read ITs, clear pending ones
    si4355_get_int_status(0u, 0u, 0u);
    
    // Get part info
    si4355_part_info();
}

U8 gRadio_CheckReceived(void)
{
    if (RF_NIRQ == FALSE)
    {
        /* Read ITs, clear pending ones */
        si4355_get_int_status(0u, 0u, 0u);
        
        /* check the reason for the IT */
        if (Si4355Cmd.GET_INT_STATUS.PH_PEND & SI4355_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT)
        {
            /* Packet RX */
            si4355_read_rx_fifo(sizeof(tRadioPacket), (U8 *) &RadioPacket);
            
            /* Generate beep */
            ReceiverDemo_InternalData.ReceiverDemo_BeepLength = 128u;
            StartTimer3(0xD025);  /* ~1kHz */
            
            return TRUE;
        }
        return FALSE;
    }
}

void Radio_StartRX(U8 channel)
{
    // Read ITs, clear pending ones
    si4355_get_int_status(0u, 0u, 0u);
    
    /* Start Receiving packet, channel 0, START immediately, Packet size by PH */
    si4355_start_rx(channel, 0u, 0u,
                    SI4355_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
                    SI4355_CMD_START_RX_ARG_RXVALID_STATE_ENUM_SLEEP,
                    SI4355_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

U8 bRadio_Check_Ezconfig(U16 crc)
{
    si4355_ezconfig_check(crc);
    
    return radioCmd[0u];
}

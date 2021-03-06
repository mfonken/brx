#include "types.h"
#include "config.h"
#include "radio.h"
#include "comm.h"
#include "si4355.h"
#include "si4355_defs.h"
#include "radio_config.h"
#include "spi.h"

U8 const Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;
tRadioConfiguration RadioConfiguration = RADIO_CONFIGURATION_DATA;
tRadioConfiguration *pRadioConfiguration = &RadioConfiguration;
tRadioPacket RadioPacket;

void Radio_PowerUp( void )
{
    U16 wDelay = 0u;
    
    //si4355_reset();
//    for( ; wDelay < 50; wDelay++);//pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++ );
    radio_comm_PollCTS();
}

void Radio_Init( void )
{
  /* Power Up the radio chip */
  Radio_PowerUp();

  /* Load radio configuration */
  while( SUCCESS != si4355_configuration_init( pRadioConfiguration->Radio_ConfigurationArray ) )
  {
    /* Power Up the radio chip */
    Radio_PowerUp();
  }
  while(1);
  // Read ITs, clear pending ones
  si4355_get_int_status(0u, 0u, 0u);
}

U8 Radio_CheckReceived( void )
{
    if( !IRQ_PIN )
    {
        /* Read ITs, clear pending ones */
        si4355_get_int_status(0u, 0u, 0u);
        
        /* check the reason for the IT */
        if (Si4355Cmd.GET_INT_STATUS.PH_PEND & SI4355_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT)
        {
            /* Packet RX */
            si4355_read_rx_fifo( sizeof( tRadioPacket ), ( U8 * ) &RadioPacket );
            return 1;
        }
    }
    return 0;
}

void Radio_StartRX( U8 channel )
{
    // Read ITs, clear pending ones
    si4355_get_int_status( 0u, 0u, 0u );
    
    /* Start Receiving packet, channel 0, START immediately, Packet size by PH */
    si4355_start_rx( channel, 0u, 0u,
                     SI4355_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
                     SI4355_CMD_START_RX_ARG_RXVALID_STATE_ENUM_SLEEP,
                     SI4355_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

U8 Radio_Check_Ezconfig( U16 crc )
{
    si4355_ezconfig_check( crc );
    
    return radioCmd[0u];
}

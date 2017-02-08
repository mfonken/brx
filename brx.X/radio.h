#ifndef RADIO_H
#define RADIO_H

#define EZCONFIG_ARRAY_SIZE     256u
#define EZCONFIG_RADIO_CFG_SIZE 202u

/*****************************************************************************
 *  Global Typedefs & Enums
 *****************************************************************************/
typedef struct
{
    U8   Radio_Configuration[EZCONFIG_RADIO_CFG_SIZE];
    U16  Radio_Configuration_CRC;
    
    U8   Radio_BOOT_OPTIONS;
    U8   Radio_XTAL_OPTIONS;
    U32  Radio_XO_FREQ;
    
    U8   Radio_INT_CTL_ENABLE;
    U8   Radio_INT_CTL_PH_ENABLE;
    U8   Radio_INT_CTL_MODEM_ENABLE;
    U8   Radio_INT_CTL_CHIP_ENABLE;
    
    U8   Radio_FRR_CTL_A_MODE;
    U8   Radio_FRR_CTL_B_MODE;
    U8   Radio_FRR_CTL_C_MODE;
    U8   Radio_FRR_CTL_D_MODE;
    
    U8   Radio_SYNC_BITS_31_24;
    U8   Radio_SYNC_BITS_23_16;
    
    U8   Radio_PA_PWR_LVL;
    
    U8   Radio_EZCONFIG_MODULATION;
    U8   Radio_EZCONFIG_XO_TUNE;
    
    U8   Radio_FREQ_CONTROL_INTE;
    U8   Radio_FREQ_CONTROL_FRAC_2;
    U8   Radio_FREQ_CONTROL_FRAC_1;
    U8   Radio_FREQ_CONTROL_FRAC_0;
    
    U8   Radio_FREQ_CONTROL_CHANNEL_STEP_SIZE_1;
    U8   Radio_FREQ_CONTROL_CHANNEL_STEP_SIZE_0;
    
    U8   Radio_GPIO0_PIN_CFG;
    U8   Radio_GPIO1_PIN_CFG;
    U8   Radio_GPIO2_PIN_CFG;
    U8   Radio_GPIO3_PIN_CFG;
    U8   Radio_GPIO_NIRQ_MODE;
    U8   Radio_GPIO_SDO_MODE;
    U8   Radio_GPIO_GEN_CONFIG;
    
    U8   Radio_Mode_After_Power_Up;
    
    U16  Radio_Delay_Cnt_After_Reset;
} tEzConfigArray;

extern tEzConfigArray config;
extern tRadioPacket RadioPacket;

/*****************************************************************************
 *  Global Function Declarations
 *****************************************************************************/
void  Radio_Init(void);
void  Radio_SetChip();
U8    Radio_CheckReceived(void);
void  Radio_StartRX(U8);

#endif /* radio_h */

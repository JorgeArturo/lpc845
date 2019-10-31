/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v6.0
processor: LPC845
package_id: LPC845M301JBD48
mcu_data: ksdk2_0
processor_version: 6.0.2
board: LPC845BREAKOUT
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'msg'
- type_id: 'msg_6e2baaf3b97dbeef01c0043275f9a0e7'
- global_messages: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * UbloxUsartGPS initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'UbloxUsartGPS'
- type: 'lpc_miniusart'
- mode: 'interrupt'
- type_id: 'lpc_miniusart_d84319ec2ca0cfec3b3de86986cd7d44'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'USART1'
- config_sets:
  - fsl_usart:
    - usartConfig:
      - clockSource: 'FunctionClock'
      - clockSourceFreq: 'BOARD_BootClockFRO30M'
      - baudRate_Bps: '9600'
      - syncMode: 'kUSART_SyncModeDisabled'
      - parityMode: 'kUSART_ParityDisabled'
      - stopBitCount: 'kUSART_OneStopBit'
      - bitCountPerChar: 'kUSART_8BitsPerChar'
      - loopback: 'false'
      - enableRx: 'true'
      - enableTx: 'true'
      - clockPolarity: 'kUSART_RxSampleOnFallingEdge'
      - enableContinuousSCLK: 'false'
    - quick_selection: 'QS_USART_1'
  - Interrupt_cfg:
    - interrupts: 'kUSART_RxReadyInterruptEnable'
    - interrupt_vectors:
      - enable_rx_tx_irq: 'false'
      - interrupt_rx_tx:
        - IRQn: 'USART1_IRQn'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'true'
        - handler_custom_name: 'UbloxUsartGPS_IRQHandler'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const usart_config_t UbloxUsartGPS_config = {
  .baudRate_Bps = 9600,
  .syncMode = kUSART_SyncModeDisabled,
  .parityMode = kUSART_ParityDisabled,
  .stopBitCount = kUSART_OneStopBit,
  .bitCountPerChar = kUSART_8BitsPerChar,
  .loopback = false,
  .enableRx = true,
  .enableTx = true,
  .clockPolarity = kUSART_RxSampleOnFallingEdge,
  .enableContinuousSCLK = false
};

void UbloxUsartGPS_init(void) {
  /* USART1 peripheral initialization */
  USART_Init(UBLOXUSARTGPS_PERIPHERAL, &UbloxUsartGPS_config, UBLOXUSARTGPS_CLOCK_SOURCE);
  USART_EnableInterrupts(UBLOXUSARTGPS_PERIPHERAL, kUSART_RxReadyInterruptEnable);
}

/***********************************************************************************************************************
 * TelitUsartGSM initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'TelitUsartGSM'
- type: 'lpc_miniusart'
- mode: 'interrupt'
- type_id: 'lpc_miniusart_d84319ec2ca0cfec3b3de86986cd7d44'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'USART2'
- config_sets:
  - fsl_usart:
    - usartConfig:
      - clockSource: 'FunctionClock'
      - clockSourceFreq: 'BOARD_BootClockFRO30M'
      - baudRate_Bps: '9600'
      - syncMode: 'kUSART_SyncModeDisabled'
      - parityMode: 'kUSART_ParityDisabled'
      - stopBitCount: 'kUSART_OneStopBit'
      - bitCountPerChar: 'kUSART_8BitsPerChar'
      - loopback: 'false'
      - enableRx: 'true'
      - enableTx: 'true'
      - clockPolarity: 'kUSART_RxSampleOnFallingEdge'
      - enableContinuousSCLK: 'false'
    - quick_selection: 'QS_USART_1'
  - Interrupt_cfg:
    - interrupts: 'kUSART_RxReadyInterruptEnable'
    - interrupt_vectors:
      - enable_rx_tx_irq: 'false'
      - interrupt_rx_tx:
        - IRQn: 'USART2_IRQn'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'true'
        - handler_custom_name: 'TelitUsartGSM_IRQHandler'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const usart_config_t TelitUsartGSM_config = {
  .baudRate_Bps = 9600,
  .syncMode = kUSART_SyncModeDisabled,
  .parityMode = kUSART_ParityDisabled,
  .stopBitCount = kUSART_OneStopBit,
  .bitCountPerChar = kUSART_8BitsPerChar,
  .loopback = false,
  .enableRx = true,
  .enableTx = true,
  .clockPolarity = kUSART_RxSampleOnFallingEdge,
  .enableContinuousSCLK = false
};

void TelitUsartGSM_init(void) {
  /* USART2 peripheral initialization */
  USART_Init(TELITUSARTGSM_PERIPHERAL, &TelitUsartGSM_config, TELITUSARTGSM_CLOCK_SOURCE);
  USART_EnableInterrupts(TELITUSARTGSM_PERIPHERAL, kUSART_RxReadyInterruptEnable);
}

/***********************************************************************************************************************
 * MRT_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'MRT_1'
- type: 'mrt'
- mode: 'general_config'
- type_id: 'mrt_ec4ff9f008b2eee803e5f398b3b3325f'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'MRT0'
- config_sets:
  - fsl_mrt:
    - mrtOperationMode: 'HSM'
    - clockSettingMRT:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'BOARD_BootClockFRO30M'
    - mrtChannels:
      - 0:
        - mrtChannelPrefixID: 'Channel_0'
        - channelNumber: 'kMRT_Channel_0'
        - timerMode: 'kMRT_RepeatMode'
        - timerValueStr: '1000000'
        - startTimer: 'false'
        - enableInterruptRequest: 'true'
    - interruptVector:
      - enableInterrupt: 'true'
      - interrupt:
        - IRQn: 'MRT0_IRQn'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const mrt_config_t MRT_1_config = {
  .enableMultiTask = false
};

void MRT_1_init(void) {
  /* MRT0 peripheral initialization */
  MRT_Init(MRT_1_PERIPHERAL, &MRT_1_config);
  /* MRT channel 0 of MRT0 peripheral initialization */
  MRT_SetupChannelMode(MRT_1_PERIPHERAL, MRT_1_CHANNEL_0, MRT_1_CHANNEL_0_MODE);
  /* MRT channel 0 interrupt of MRT0 peripheral initialization */
  MRT_EnableInterrupts(MRT_1_PERIPHERAL, MRT_1_CHANNEL_0, kMRT_TimerInterruptEnable);
  /* Enable interrupt MRT0_IRQn request in the NVIC */
  EnableIRQ(MRT_1_IRQN);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  UbloxUsartGPS_init();
  TelitUsartGSM_init();
  MRT_1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}

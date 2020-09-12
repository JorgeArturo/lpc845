/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Used DMA device. */
#define DMA0_DMA_BASEADDR DMA0
/* DMA0 interrupt vector ID (number). */
#define DMA0_IRQN DMA0_IRQn

  /* Channel CH0 definitions */
/* Selected DMA channel number. */
#define DMA0_CH0_DMA_CHANNEL 0
/* TCD structure index 0 definition */
#define DMA0_CH0_TCD0_config DMA0_CH0_TCDs_config[0]

  /* Channel CH1 definitions */
/* Selected DMA channel number. */
#define DMA0_CH1_DMA_CHANNEL 1
/* TCD structure index 0 definition */
#define DMA0_CH1_TCD0_config DMA0_CH1_TCDs_config[0]

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern dma_handle_t DMA0_CH0_Handle;
/* DMA0 channel CH0 TCD array */
extern dma_descriptor_t DMA0_CH0_TCDs_config[1];
extern dma_handle_t DMA0_CH1_Handle;
/* DMA0 channel CH1 TCD array */
extern dma_descriptor_t DMA0_CH1_TCDs_config[1];

/***********************************************************************************************************************
 * Callback functions
 **********************************************************************************************************************/
/* DMA callback function for the 0 channel.*/
extern void dma0_callbacks(struct _dma_handle *, void *, bool, uint32_t);
/* DMA callback function for the 1 channel.*/
extern void dma0_callbacks_ch1(struct _dma_handle *, void *, bool, uint32_t);

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */

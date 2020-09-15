/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Tutorial_1_DMA_2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_inputmux.h"
#include "fsl_power.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

adc_result_info_t dstAddr[3];
uint8_t srcAddr[6];

uint32_t RunSEQ = 0;

enum{RunADC = 10,WaitADC,ProcessADC,SendData,Delay};

typedef struct FLAGS_DMA{

	unsigned flag_adc:1;
	unsigned flag_tx:1;
	unsigned spare2:1;
	unsigned spare3:1;
	unsigned spare4:1;
	unsigned spare5:1;
	unsigned spare6:1;
	unsigned spare7:1;

}flags_dma;

flags_dma flags;

/* TODO: insert other definitions and declarations here. */

void Callback_DMA0_CH1(struct _dma_handle *handle, void *param, bool transferDone, uint32_t tcds){

	if(tcds == kDMA_IntA){

		flags.flag_tx = 1;

	}

}


/*
 * @brief   Application entry point.
 */
int main(void) {

	POWER_DisablePD(kPDRUNCFG_PD_ADC0);

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    PRINTF("Data transfer ADC->Memory->Process->TX1\n");

    RunSEQ = RunADC;

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	switch(RunSEQ){

			case RunADC:

				ADC_DoSoftwareTriggerConvSeqA(ADC0_PERIPHERAL);

				RunSEQ = WaitADC;

				break;

			case WaitADC:

				if((ADC_GetStatusFlags(ADC0_PERIPHERAL)&kADC_ConvSeqAInterruptFlag) == kADC_ConvSeqAInterruptFlag){

					RunSEQ = ProcessADC;

				}else
					RunSEQ = WaitADC;

				break;

			case ProcessADC:

				ADC_GetChannelConversionResult(ADC0_PERIPHERAL,1,&dstAddr[0]);
				ADC_GetChannelConversionResult(ADC0_PERIPHERAL,2,&dstAddr[1]);
				ADC_GetChannelConversionResult(ADC0_PERIPHERAL,3,&dstAddr[2]);

				srcAddr[0] = (uint8_t)(((uint32_t)dstAddr[0].result >> 4) & 0xFF);
				srcAddr[1] = (uint8_t)(((uint32_t)dstAddr[0].result >> 12) & 0x0F);

				srcAddr[2] = (uint8_t)(((uint32_t)dstAddr[1].result >> 4) & 0xFF);
				srcAddr[3] = (uint8_t)(((uint32_t)dstAddr[1].result >> 12) & 0x0F);

				srcAddr[4] = (uint8_t)(((uint32_t)dstAddr[2].result >> 4) & 0xFF);
				srcAddr[5] = (uint8_t)(((uint32_t)dstAddr[2].result >> 12) & 0x0F);

				DMA_StartTransfer(&DMA0_CH1_Handle);
				RunSEQ = SendData;

				break;

			case SendData:

				if(flags.flag_tx){

					flags.flag_tx = 0;
					RunSEQ = Delay;

				}else
					RunSEQ = SendData;

				break;

			case Delay:

				for(uint32_t t = 1000000;t>0;t--);
				RunSEQ = RunADC;

				break;

			default:

				break;


    	}


    }
    return 0 ;
}

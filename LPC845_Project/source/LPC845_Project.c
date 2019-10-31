/*
 * Copyright 2016-2019 NXP
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
 * @file    LPC845_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

uint8_t bufferGPS[2048];
uint16_t gps_index = 0;
uint8_t gps_search = 0;

/* TODO: insert other definitions and declarations here. */

void delay(void){

	uint32_t t = 0;

	for(t = 0; t<2000000; t++);

}


/*Interrupt when the GPS interrupt finished to receive all the data*/

void MRT_1_IRQHANDLER(void){

	MRT_ClearStatusFlags(MRT_1_PERIPHERAL,MRT_1_CHANNEL_0,kMRT_TimerInterruptFlag);
	MRT_StopTimer(MRT_1_PERIPHERAL,MRT_1_CHANNEL_0);

	bufferGPS[gps_index] = 0;

	gps_search = 1;
	gps_index = 0;


}


/*Interrupt in the GPS port*/

void UbloxUsartGPS_IRQHandler(void){

	if(USART_GetStatusFlags(UBLOXUSARTGPS_PERIPHERAL) & kUSART_RxReady){

		USART_ClearStatusFlags(UBLOXUSARTGPS_PERIPHERAL,kUSART_RxReady);

		bufferGPS[gps_index] = USART_ReadByte(UBLOXUSARTGPS_PERIPHERAL);

		if(gps_index == 0)
			MRT_StartTimer(MRT_1_PERIPHERAL, MRT_1_CHANNEL_0, MRT_1_CHANNEL_0_TICKS);
		else
			MRT_UpdateTimerPeriod(MRT_1_PERIPHERAL,MRT_1_CHANNEL_0,MRT_1_CHANNEL_0_TICKS,true);
			//CTIMER_StartTimer(CTIMER_1_PERIPHERAL);

		gps_index++;

	}

}


/*Interrupt in the TELIT port*/

void TelitUsartGSM_IRQHandler(void){

	if(USART_GetStatusFlags(TELITUSARTGSM_PERIPHERAL) & kUSART_RxReady){

		USART_ClearStatusFlags(TELITUSARTGSM_PERIPHERAL,kUSART_RxReady);


	}

}


void UbloxNMEAParse(uint8_t* data){


	if (*data++==0){




	}


}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    DisableIRQ(UBLOXUSARTGPS_USART_IRQN);
    DisableIRQ(TELITUSARTGSM_USART_IRQN);

    PRINTF("Hello World\n");

    LED_GREEN_INIT(0);

    EnableIRQ(UBLOXUSARTGPS_USART_IRQN);

    /* Force the counter to be placed into memory. */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	if(gps_search){

    		DisableIRQ(UBLOXUSARTGPS_USART_IRQN);

    		gps_search = 0;
    		LED_GREEN_TOGGLE();
    		PRINTF("%s",bufferGPS);
    		//CTIMER_Reset(CTIMER_1_PERIPHERAL);

    		EnableIRQ(UBLOXUSARTGPS_USART_IRQN);

    	}

    }
    return 0 ;
}

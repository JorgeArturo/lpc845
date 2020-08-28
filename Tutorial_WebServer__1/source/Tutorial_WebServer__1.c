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
 * @file    Tutorial_WebServer__1.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
#include <string.h>
/* TODO: insert other include files here. */

const char wp[] = {"<!DOCTYPEhtml>  <html>  <head>  <style>  table{  font-family:arial,sans-serif;  border-collapse:collapse;  width:100%;  }    td,th{  border:1pxsolid#dddddd;  text-align:left;  padding:8px;  }    tr:nth-child(even){  background-color:#dddddd;  }  </style>  </head>  <body>    <h2>HTMLTable</h2>    <table>  <tr>  <th>Company</th>  <th>Contact</th>  <th>Country</th>  </tr>  <tr>  <td>AlfredsFutterkiste</td>  <td>MariaAnders</td>  <td>Germany</td>  </tr>  <tr>  <td>CentrocomercialMoctezuma</td>  <td>FranciscoChang</td>  <td>Mexico</td>  </tr>  <tr>  <td>ErnstHandel</td>  <td>RolandMendel</td>  <td>Austria</td>  </tr>  <tr>  <td>IslandTrading</td>  <td>HelenBennett</td>  <td>UK</td>  </tr>  <tr>  <td>LaughingBacchusWinecellars</td>  <td>YoshiTannamuri</td>  <td>Canada</td>  </tr>  <tr>  <td>MagazziniAlimentariRiuniti</td>  <td>GiovanniRovelli</td>  <td>Italy</td>  </tr>  </table>    </body>  </html>\0"};


unsigned int wp_len;

char r[1024];
uint8_t flagrx = 0;

/* TODO: insert other definitions and declarations here. */

/* USART1_IRQn interrupt handler */
void USART1_USART_IRQHANDLER(void) {
  /*  Place your code here */

	if((USART_GetStatusFlags(USART1_PERIPHERAL) & kUSART_RxReady) == kUSART_RxReady){

		USART_ClearStatusFlags(USART1_PERIPHERAL,kUSART_RxReady);

		flagrx = 1;

		USART_ReadBlocking(USART1_PERIPHERAL,&r,sizeof(r));
	}

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

int8_t ESP8266_Response(char* resp,char* s){

	char* token;

	flagrx = 0;
	while(!flagrx);
	flagrx = 0;

	token = strtok(resp,"\r\n");

	while(token != NULL){
		PRINTF("--> %s\r\n\0",token);
		if(strcmp(token,s) == 0)
			return 1;

		token = strtok(NULL,"\r\n");


	}

	return 0;


}

int8_t ESP8266_Init(char* SSID,char* pwd){

	char con[80];

	USART_WriteBlocking(USART1_PERIPHERAL,"AT+RST\r\n",8);
	for(uint32_t t=2000000;t>0;t--);

	USART_WriteBlocking(USART1_PERIPHERAL,"ATE0\r\n",6);
	for(uint32_t t=1000000;t>0;t--);

	flagrx = 0;
	USART_WriteBlocking(USART1_PERIPHERAL,"AT\r\n",4);
    if(!ESP8266_Response(&r,"OK"))
    	return -1;

	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CWMODE_CUR=1\r\n",17);
    if(!ESP8266_Response(&r,"OK"))
    	return -2;

    strcpy(con,"AT+CWJAP_CUR=\"");
    strcat(con,SSID);
    strcat(con,"\",\"");
    strcat(con,pwd);
    strcat(con,"\"\r\n");

    //SSID + PWD

	USART_WriteBlocking(USART1_PERIPHERAL,&con,strlen(con));

    do{
    	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CIPSTATUS\r\n",14);
    }while(ESP8266_Response(&r,"busy p..."));

    //for(uint32_t t=5000000;t>0;t--);
    //Multi-Connections
	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CIPMUX=1\r\n",13);
    if(!ESP8266_Response(&r,"OK"))
    	return -4;

    //Server Port default 80
	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CIPSERVER=1,80\r\n",19);
    if(!ESP8266_Response(&r,"OK"))
    	return -5;

    //Timeout Client to 30 s

	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CIPSTO=30\r\n",14);
    if(!ESP8266_Response(&r,"OK"))
    	return -6;


    return 1;

}

void ESP8266_WebServer(void){

	char clen[5] = {0,0,0,0,0};
	char con[25];
	unsigned int con_len;
	char* token;
	int _n = -1;

	wp_len = sizeof(wp);

	flagrx = 0;
	while(!flagrx);
	flagrx = 0;

	token = strtok(r,",\r\n");

	while(token != NULL){
		if(strcmp(token,"+IPD")==0)
			break;

		token = strtok(NULL,",\r\n");

	}

	if(strcmp(token,"+IPD")==0){

		token = strtok(NULL,",\r\n");

		_n = atoi(token);

		if(_n >= 0 && _n<=5){

			sprintf(clen,"%u",wp_len);
			strcpy(con,"AT+CIPSEND=");
			strcat(con,token);
			strcat(con,",");
			strcat(con,clen);
			strcat(con,"\r\n\0");

			con_len = strlen(con);

			USART_WriteBlocking(USART1_PERIPHERAL,&con,con_len);
			for(uint32_t t=1000000;t>0;t--);

			USART_WriteBlocking(USART1_PERIPHERAL,&wp,wp_len);
			for(uint32_t t=1000000;t>0;t--);

		}

	}

	USART_WriteBlocking(USART1_PERIPHERAL,"AT+CIPCLOSE=5\r\n",15);
}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Esp8266 WEBserver\n");

    if(ESP8266_Init("TP-LINK_7456", "67320004") == 1)

    	PRINTF("Connected\r\n");

    else{

    	PRINTF("Error\r\n");

    	while(1);

    }

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	ESP8266_WebServer();

    }
    return 0 ;
}

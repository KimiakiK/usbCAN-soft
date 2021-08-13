/*
 * drv_uart.c
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

/********** Include **********/

#include "common_type.h"
#include "drv_uart.h"

/********** Define **********/

#define UART_TIMEOUT	(100)

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

extern UART_HandleTypeDef huart1;

/********** Function Prototype **********/

/********** Function **********/

/*=== 初期化関数 ===*/
void DrvUartInit(void)
{
	
}

/*=== UART同期送信関数 ===*/
void DrvUartSyncTransmit(uint8_t* data, uint16_t size)
{
	HAL_UART_Transmit(&huart1, data, size, UART_TIMEOUT);
}

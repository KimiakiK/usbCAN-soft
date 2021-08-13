/*
 * drv_uart.h
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

#ifndef INC_DRV_UART_H_
#define INC_DRV_UART_H_

/********** Include **********/

/********** Define **********/

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

void DrvUartInit(void);
void DrvUartSyncTransmit(uint8_t* data, uint16_t size);

#endif /* INC_DRV_UART_H_ */

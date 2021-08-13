/*
 * apl_cantext.c
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

/********** Include **********/

#include "common_type.h"
#include "drv_can.h"
#include "drv_uart.h"
#include "apl_cantext.h"

/********** Define **********/

/********** Type **********/

/********** Constant **********/

const uint8_t hex_ascii[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/********** Variable **********/

/********** Function Prototype **********/

uint16_t makeMessageText(uint8_t* text, can_message_t* message);
uint16_t makeHexText(uint8_t* text, uint32_t number, uint8_t digit);
uint16_t addSpace(uint8_t* text);
uint16_t addReturn(uint8_t* text);

/********** Function **********/

/*=== 初期化関数 ===*/
void AplCantextInit(void)
{

}

/*=== 周期関数 ===*/
void AplCantextMain(void)
{
	can_message_t rx_message;
	rx_state_t rx_state;
	uint8_t text[50];
	uint8_t length;

	rx_state = McalCanReceive(&rx_message);

	if (rx_state == RX_OK) {
		length = makeMessageText(text, &rx_message);
		DrvUartSyncTransmit(text, length);
	}
}

uint16_t makeMessageText(uint8_t* text, can_message_t* message)
{
	uint16_t length;
	uint8_t loop;

	length = 0;

	if (message->id_type == ID_BASIC) {
		length += makeHexText(&text[length], message->id, 3);
	} else {
		length += makeHexText(&text[length], message->id, 8);
	}

	length += addSpace(&text[length]);

	length += makeHexText(&text[length], message->dlc, 1);

	for (loop=0; loop<message->dlc; loop++) {
		length += addSpace(&text[length]);
		length += makeHexText(&text[length], message->data[loop], 2);
	}

	length += addReturn(&text[length]);

	return length;
}
uint16_t makeHexText(uint8_t* text, uint32_t number, uint8_t digit)
{
	uint8_t index;
	index = 0;
	
	for (;digit>0; digit--) {
		text[index] = hex_ascii[(number >> ((digit-1)*4)) & 0xF];
		index++;
	}
	return index;
}

uint16_t addSpace(uint8_t* text)
{
	text[0] = ' ';
	return 1;
}

uint16_t addReturn(uint8_t* text)
{
	text[0] = 0x0D;
	text[1] = 0x0A;
	return 2;
}

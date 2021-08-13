/*
 * drv_can.c
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

/********** Include **********/

#include "common_type.h"
#include "mcal_can.h"
#include "drv_can.h"

/********** Define **********/

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

/********** Function **********/

/*=== 初期化関数 ===*/
void DrvCanInit(void)
{

}

/*=== CAN受信メッセージ取得関数 ===*/
rx_state_t DrvCanGetRxMessage(can_message_t* message)
{
	return McalCanReceive(message);
}

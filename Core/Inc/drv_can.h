/*
 * drv_can.h
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

#ifndef INC_DRV_CAN_H_
#define INC_DRV_CAN_H_

/********** Include **********/

#include "mcal_can.h"

/********** Define **********/

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

void DrvCanInit(void);
rx_state_t DrvCanGetRxMessage(can_message_t* message);

#endif /* INC_DRV_CAN_H_ */

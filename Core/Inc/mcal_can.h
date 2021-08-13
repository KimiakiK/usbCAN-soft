/*
 * mcal_can.h
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

#ifndef SRC_MCAL_CAN_H_
#define SRC_MCAL_CAN_H_

/********** Include **********/

/********** Define **********/

#define DATA_SIZE_MAX		(8)

typedef enum rx_state_enum {
	RX_EMPTY = 0,
	RX_OK
} rx_state_t;

typedef enum id_type_enum {
	ID_BASIC = 0,
	ID_EXTEND
} id_type_t;

/********** Type **********/

typedef struct can_message_struct {
	uint32_t id;
	id_type_t id_type;
	uint8_t dlc;
	uint8_t data[DATA_SIZE_MAX];
} can_message_t;

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

void McalCanInit(void);
rx_state_t McalCanReceive(can_message_t* message);

#endif /* SRC_MCAL_CAN_H_ */

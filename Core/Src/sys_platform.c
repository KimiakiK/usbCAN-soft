/*
 * sys_platform.c
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

/********** Include **********/

#include "common_type.h"
#include "apl_cantext.h"
#include "drv_can.h"
#include "drv_uart.h"
#include "mcal_can.h"
#include "sys_platform.h"

/********** Define **********/

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

/********** Function **********/

/*=== 初期化関数 ===*/
void SysPlatformInit(void)
{
	McalCanInit();
	DrvCanInit();
	DrvUartInit();
	AplCantextInit();
}

/*=== 周期関数 ===*/
void SysPlatformMain(void)
{
	AplCantextMain();
}

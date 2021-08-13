/*
 * mcal_can.c
 *
 *  Created on: 2021/08/09
 *      Author: kimi
 */

/********** Include **********/

#include "common_type.h"
#include "mcal_can.h"

/********** Define **********/

/********** Type **********/

/********** Constant **********/

/********** Variable **********/

/********** Function Prototype **********/

/********** Function **********/

/*=== 初期化関数 ===*/
void McalCanInit(void)
{
	// CAN マスタ制御レジスタ（CAN_MCR）
	CAN->MCR = 0x00010041;		// 自動バスオフ復帰、自動再送信、スリープ解除、初期化モード遷移
	// CAN 割り込み有効レジスタ（CAN_IER）
	CAN->IER = 0x00000000;		// 割り込み禁止
	// CAN ビットタイミングレジスタ（CAN_BTR）
	// tq = 36MHz / 4 = 111.1111111ns
	// SYNC_SEG = 1tq
	// SEG1 = 1 + TS1 = 14tq
	// SEG2 = 1 + TS2 = 4tq
	// BitTime = tq * 18 = 1999.99ns
	// BaudRate = 1 / BitTime = 500kbps
	CAN->BTR = 0x022d0003;
	
	// CAN フィルタマスタレジスタ（CAN_FMR）
	CAN->FMR = 0x2A1C0E01;		// フィルタの初期化モード
	// CAN フィルタモードレジスタ（CAN_FM1R）
	CAN->FM1R = 0x00000000;		// 全フィルタ識別子マスクモード
	// CAN フィルタスケールレジスタ（CAN_FS1R）
	CAN->FS1R = 0x00003FFF;		// 全フィルタシングル 32 ビットスケール設定
	// CAN フィルタ FIFO 割当てレジスタ（CAN_FFA1R）
	CAN->FFA1R = 0x00000000;	// 全フィルタFIFO0に割り当て
	// CAN フィルタバンク i レジスタ x （CAN_FiRx）
	CAN->sFilterRegister[0].FR1 = 0x00000000;	// 識別子フィルタはマスクで無効にするので初期値
	CAN->sFilterRegister[0].FR2 = 0x00000000;	// 全ビット無視（このビットは比較に使用されません）
	// CAN フィルタアクティベーションレジスタ（CAN_FA1R）
	CAN->FA1R = 0x00000001;		// フィルタ0のみアクティブ
	
	// フィルタ有効化
	CAN->FMR = 0x2A1C0E00;
	// 通常モード遷移
	CAN->MCR &= 0xFFFFFFFE;
}

/*=== CAN受信関数 ===*/
rx_state_t McalCanReceive(can_message_t* message)
{
	rx_state_t rx_state;

	rx_state = RX_EMPTY;

	// 受信FIFOのペンディング確認(CAN_RF0R ビット 1:0 FMP0[1:0])
	if ( (CAN->RF0R & 0x00000003) > 0) {
		// フレーム種別判定(CAN_RIxR ビット 1 RTR)
		if ( (CAN->sFIFOMailBox[0].RIR & 0x00000002) == 0) {
			// データフレーム
			// 受信メッセージあり
			rx_state = RX_OK;
			// IDの種類を判定(CAN_RIxR ビット 2 IDE)
			if ( (CAN->sFIFOMailBox[0].RIR & 0x00000004) == 0) {
				// 標準識別子
				message->id_type = ID_BASIC;
				message->id = CAN->sFIFOMailBox[0].RIR >> 21;
			} else {
				// 拡張識別子
				message->id_type = ID_EXTEND;
				message->id = CAN->sFIFOMailBox[0].RIR >> 3;
			}
			// DLC(CAN_RDTxR ビット 3:0 DLC[3:0])
			message->dlc = CAN->sFIFOMailBox[0].RDTR & 0x0000000F;
			// データ(CAN_RDHxR, CAN_RDLxR)
			message->data[0] = (uint8_t)( (CAN->sFIFOMailBox[0].RDLR & 0x000000FF) >> 0);
			message->data[1] = (uint8_t)( (CAN->sFIFOMailBox[0].RDLR & 0x0000FF00) >> 8);
			message->data[2] = (uint8_t)( (CAN->sFIFOMailBox[0].RDLR & 0x00FF0000) >> 16);
			message->data[3] = (uint8_t)( (CAN->sFIFOMailBox[0].RDLR & 0xFF000000) >> 24);
			message->data[4] = (uint8_t)( (CAN->sFIFOMailBox[0].RDHR & 0x000000FF) >> 0);
			message->data[5] = (uint8_t)( (CAN->sFIFOMailBox[0].RDHR & 0x0000FF00) >> 8);
			message->data[6] = (uint8_t)( (CAN->sFIFOMailBox[0].RDHR & 0x00FF0000) >> 16);
			message->data[7] = (uint8_t)( (CAN->sFIFOMailBox[0].RDHR & 0xFF000000) >> 24);
		} else {
			// リモートフレーム
			// 処理無し
		}
		
		// FIFO開放(CAN_RF0R ビット 5 RFOM0)
		CAN->RF0R |= 0x00000020;
	}

	return rx_state;
}

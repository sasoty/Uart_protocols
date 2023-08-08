/*
 * Push.c
 *
 *  Created on: Aug 4, 2023
 *      Author: Minh Nhat
 */

#include "Push.h"

extern UART_HandleTypeDef huart2;

void Push_Cmd(Cmd Cmd_Type)
{
	Tx_ResetBuf();
	Tx_RingBufferInit();
	uint8_t Cmd_buffer[3];
	Cmd_buffer[0] = STX;
	Cmd_buffer[1] = TYPE1;
	Cmd_buffer[2] = Cmd_Type;

	uint8_t TxData;
//	Std_Return Tx_Avail = Tx_RingData_Avail();
	while(!Tx_RingData_Avail()==E_NOT_OK)
	{;}
	for(int Count = 0;Count < 3;Count++)
	{
		Tx_BufStuff(Cmd_buffer[Count]);
	}

	TxData = Tx_ReadBuf();
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)&TxData,1);
}


void Push_Data(float Val)
{
	Tx_RingBufferInit();
	Crypto_Init_Out(Val);
	uint8_t TxData;
	uint8_t Cmd_buffer[2];
	Cmd_buffer[0] = STX;
	Cmd_buffer[1] = TYPE2;
	while(!Tx_RingData_Avail()==E_NOT_OK)
	{;}
	for(int Count=0; Count < 2;Count++)
	{
		Tx_BufStuff(Cmd_buffer[Count]);
	}
	uint8_t Length = Crypto_Extract();
	Tx_BufStuff(Length);
	for(int Count = 0; Count < Length; Count++)
	{
		Tx_BufStuff(Crypto_BufferStuff());
	}

	//Call back frame from Crypto

	TxData = Tx_ReadBuf();
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)&TxData,1);
}




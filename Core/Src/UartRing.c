/*
 * UartRing.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ngocn
 */

#include "UartRing.h"



/**
 * For Interrupt
 */
RingContext_Type Buffer;
RingContext_Type *RingBuffer;

/**
 * Normal Variables
 */
uint8_t Test_Uart_Ring_Buf[MAX_BUFFER_SIZE];
uint8_t Test_Uart_Ring_Write_Index = 0;
uint8_t Test_Uart_Ring_Read_Index = 0;
uint8_t Test_RealBuf[MAX_BUFFER_SIZE];



void RingBufferInit(void)
{
	RingBuffer = &Buffer;
	RingBuffer->Head = 0;
	RingBuffer->Tail = 0;

}
void BufferStuff(uint8_t Data)
{
	RingBuffer->Buffer[RingBuffer->Head] = Data;
	RingBuffer->Head++ ;
	if(RingBuffer->Head == MAX_BUFFER_SIZE)
	{
		RingBuffer->Head = 0;
	}
}

Std_Return RingData_Avail(void)
{
	Std_Return Retval = E_NOT_OK;
	if(RingBuffer->Head == RingBuffer->Tail )
	{
		return Retval;
	}
	Retval = E_OK;
	return Retval;
}

//void UartRing_WriteBuf(uint8_t data)
//{
//	_RingContext->buffer[_RingContext->head] = data;
//	RingContext.head++;
//}

uint8_t ReadBuf(void)
{
	uint8_t data;
	data = RingBuffer->Buffer[RingBuffer->Tail];
	RingBuffer->Tail++;
	if(RingBuffer->Tail == MAX_BUFFER_SIZE)
	{
		RingBuffer->Tail = 0;
	}

	return data;
}

void ResetBuf(void)
{
	RingBuffer->Head = 0;
	RingBuffer->Tail = 0;
}


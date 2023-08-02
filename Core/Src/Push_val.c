/*
 * Push_val.c
 *
 *  Created on: Jan 3, 2023
 *      Author: Minh Nhat
 */




#include "Push_val.h"
#include "stm32f4xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart2;


sta_read State_Tx;
exchange_t Ret_Tx;
uint8_t Type_Tx=0;
uint8_t Len_Tx=0;
uint8_t Data_Tx=0;
uint8_t Count_Tx=0;
uint8_t Crc_Tx=0;
uint8_t Frame_Tx[4];
uint8_t Chunk_Tx[16];


void PushInit(float Val)
{
    Ret_Tx.fl = Val;
    State_Tx = SOF_;
    Type_Tx = 4;
    Data_Tx=0;
    Count_Tx = 0;
    Crc_Tx = 0;
        for(int i=0; i<Type_Tx; i++)
    {
        Frame_Tx[i]=Ret_Tx.seg[i];
    }

}

//------------------------------------------------------------------------------


//----------------------------------------------------------------------------
void EncrypData(void)
{
	int i =0;
    for(Count_Tx = 0; Count_Tx < Type_Tx; Count_Tx++)
    {
        if(Frame_Tx[Count_Tx]==STX)
        {
            Chunk_Tx[i]=FLG;
            i++;
            Chunk_Tx[i]=0x06;
        }
        else if(Frame_Tx[Count_Tx]==ETX)
        {
            Chunk_Tx[i]=FLG;
            i++;
            Chunk_Tx[i]=0x05;
        }
        else if (Frame_Tx[Count_Tx] == FLG)
        {
            Chunk_Tx[i]=FLG;
            i++;
            Chunk_Tx[i]=FLG;
        }
        else
        {
            Chunk_Tx[i]=Frame_Tx[Count_Tx];
        }
        i++;


        // switch(Frame_Tx[Count_Tx])
        // {
        //     case STX:

        // }
    }
    Len_Tx = i ;
    Count_Tx = 0;
}

//---------------------------------------------------------------------


uint8_t Pushdata(void)
{
    switch(State_Tx)
    {
        case SOF_:
        {
            Data_Tx = STX;
            State_Tx = TYP_;
            break;
        }
        case TYP_:
        {
            Data_Tx = Type_Tx;
            State_Tx = LEN_;
            break;
        }
        case LEN_:
        {
            Data_Tx = Len_Tx;
            State_Tx = DATA_;
            break;
        }
        case DATA_:
        {
            if(Count_Tx==Len_Tx)
            {
                Data_Tx = Crc_Tx;
                State_Tx = CRC_;
            }
            else
            {
                Data_Tx = Chunk_Tx[Count_Tx];
                Count_Tx++;
            }
            break;
        }
        case CRC_:
        {
            Data_Tx = ETX;
            State_Tx = EOF_;
            break;
        }
        case EOF_:
        {
            Data_Tx = ETX;
        	break;
        }

    }
    return Data_Tx;
}

//----------------------------------------------------------------------
void Putin(float Val)
{
	Tx_ResetBuf();
//	Crc_Tx = calsumup(Frame_Tx,Type_Tx);
	PushInit(Val);
    EncrypData();
    uint8_t dataout = 0;
    while(State_Tx < EOF_)
    {
    	dataout = Pushdata();
    	Tx_BufStuff(dataout);
    }
    uint8_t TxData;
	TxData = Tx_ReadBuf();
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)&TxData,1);
  //  BufferStuff(ETX);
}
void Push_cmd(cmd_type cmd)
{
	Tx_ResetBuf();
	Tx_RingBufferInit();
    uint8_t cmd_buffer[6];
    cmd_buffer[0] = STX;
    cmd_buffer[1] = TYPE1;
    cmd_buffer[2] = 1;
    cmd_buffer[3]= cmd;
    cmd_buffer[4] = 0;
    cmd_buffer[5] = ETX;

    for (int i = 0; i < 6; i++)
	{

    	Tx_BufStuff(cmd_buffer[i]);

	}
    uint8_t TxData;
	TxData = Tx_ReadBuf();
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)&TxData,1);

}
/*
Std_Return Avail = RingData_Avail();
if(Avail = E_OK)
{
    TxData = ReadBuf();
    HAL_UART_Transmit_IT(&huart1,(uint8_t *)&TxData,1);
}

Interupt
if(Avail == E_OK)
{
    TxData = ReadBuf();
    HAL_UART_Transmit_IT(&huart1,(uint8_t *)&TxData,1);
}

*/

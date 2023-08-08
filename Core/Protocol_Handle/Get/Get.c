/*
 * Get.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Minh Nhat
 */


#include "Get.h"

void Get_Init(void)
{

}



Std_Return Get_Avail(void)
{

	while(Rx_RingData_Avail() == E_NOT_OK)
	{
		;
	}
		uint8_t Cmd_Avail = E_NOT_OK;
		for(int Count = 0; Count < 8; Count++)
		{
			if(Rx_RingData_Avail() == E_OK)
			{
				if(Rx_ReadBuf()==STX)
				{
					Cmd_Avail = E_OK;
					break;
				}
			}
			else
			{
				break;
			}
		}

	return Cmd_Avail;
}

Cmd Get_Cmd(void)
{
	uint8_t Type;
	Cmd Cmd_Type;
	Type = Rx_ReadBuf();
	if(Type == TYPE1)
	{
		Cmd_Type = Rx_ReadBuf();
	}
	else
	{
		Cmd_Type = ERR_;
	}
	return Cmd_Type;

}

Std_Return Get_Val_Init(void)
{
	uint8_t Type;
	Type = Rx_ReadBuf();
	if(Type == TYPE2)
	{
		uint8_t Len = Rx_ReadBuf();
			for(int Count = 0; Count < Len; Count++)
			{
				uint8_t Data = Rx_ReadBuf();
				Crypto_In(Data);
			}
			return E_OK;
	}
	//Note
	else
	{
		return E_NOT_OK;
	}

}

float Get_Val(void)
{
	return Crypto_Compress();
}

//void Get_Checksum(void)
//{
//	uint8_t Check_sum = Rx_ReadBuf();
//}

void Get_Error(void)
{
	Rx_RingBufferInit();
	uint8_t Cmd_buffer[3];
	Cmd_buffer[0] = STX;
	Cmd_buffer[1] = TYPE1;
	Cmd_buffer[2] = ERR_;
	for(int Count = 0;Count < 3;Count++)
		{
			Rx_BufStuff(Cmd_buffer[Count]);
		}
}


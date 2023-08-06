/*
 * Error_Active.c
 *
 *  Created on: Aug 4, 2023
 *      Author: Minh Nhat
 */


#include "Error_Active.h"

static uint8_t Err_counter;
bool Error_FLG = false;


void Error_Trigger(void)
{
	Err_counter ++;
//	Error_Handler();
}

void Error_Clear(void)
{
	Err_counter = 0;
	Error_FLG = false;
}

void Error_Set(void)
{
	Error_FLG = true;
}

Std_Return Error_Counter(void)
{
	Std_Return Error_Exist;
	if(Err_counter >= 3)
	{
		Error_Exist = E_NOT_OK;
	}
	else
	{
		Error_Exist = E_OK;
	}
	return Error_Exist;
}

void Error_Handle(void)
{
	if(Error_FLG == true)
	{
		uint8_t Cmd_buffer[6]= {STX,TYPE1,1,ERR_,0,ETX};
			Err_counter ++;
		//	Std_Return Tx_Avail = Tx_RingData_Avail();
			while(!(Rx_RingData_Avail()))
			{;}
			for(int Count = 0;Count < 6;Count++)
			{
				Rx_BufStuff(Cmd_buffer[Count]);
			}
	}
	else
	{
		Err_counter = 0;
	}
}

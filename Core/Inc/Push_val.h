/*
 * Push_val.h
 *
 *  Created on: Jan 3, 2023
 *      Author: Minh Nhat
 */

#ifndef INC_PUSH_VAL_H_
#define INC_PUSH_VAL_H_


#include "stdbool.h"
#include "stdio.h"
//#include "UartRing.h"
#include "Std_Types.h"
#include "Tx_Buff.h"


#define FLG 0x07

//typedef enum
//{
//    SOF_=0,
//    TYP_,
//    LEN_,
//    DATA_,
//    CRC_,
//    EOF_,
//}sta_read;

//enum
//{
//    STX = 0x01,
//    ETX = 0X02,
//    TYPE1 = 0X03,
//    TYPE2 = 0X04,
//};

//typedef union exchange
//{
//    float fl;
//    uint8_t seg[4];
//}exchange_t;


void PushInit(float Val);

void EncrypData(void);

uint8_t Pushdata(void);

void Putin(float Val);

void Push_cmd(cmd_type cmd);

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

}

*/

#endif /* INC_PUSH_VAL_H_ */

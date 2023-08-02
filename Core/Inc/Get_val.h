/*
 * Get_val.h
 *
 *  Created on: Dec 30, 2022
 *      Author: Minh Nhat
 */

#ifndef INC_GET_VAL_H_
#define INC_GET_VAL_H_

#include "stdbool.h"
#include "stdio.h"
#include "Rx_Buff.h"
#include "Std_Types.h"

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
//
//enum
//{
//    STX = 0x01,
//    ETX = 0X02,
//    TYPE1 = 0X03,
//    TYPE2 = 0X04,
//};
//
//typedef union exchange
//{
//    float fl;
//    uint8_t seg[4];
//}exchange_t;


void GetInit(void);

sta_read GetData(void);

void DecrypData (void);

//void EncrypData(void);

float Takeout(void);

//void Takein(void);

float chunkSum(void);

cmd_type Get_cmd(void);

uint8_t Type_ret(void);

#endif /* INC_GET_VAL_H_ */

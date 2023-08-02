/*
 * Std_Types.h
 *
 *  Created on: Sep 4, 2022
 *      Author: ngocn
 *      mod : Minh Nhat
 */

#ifndef APPLICATION_USER_BOOTFUNCTION_INC_STD_TYPES_H_
#define APPLICATION_USER_BOOTFUNCTION_INC_STD_TYPES_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define MAX_BUFFER_SIZE 2048U

typedef enum
{
	E_OK = 1,
	E_NOT_OK = 0
}Std_Return;

typedef struct{
	GPIO_PinState spin1;
	GPIO_PinState spin2;

}gpin_state;

typedef enum
{
	REQ_ = 0x05,
	ACK_= 0x06,
	VAL_ = 0x07,
	ERR_ = 0x27
}cmd_type;

typedef enum
{
    SOF_=0,
    TYP_,
    LEN_,
    DATA_,
    CRC_,
    EOF_,
}sta_read;

enum
{
    STX = 0x01,
    ETX = 0X02,
    TYPE1 = 0X03,
    TYPE2 = 0X04,
};

typedef union exchange
{
    float fl;
    uint8_t seg[4];
}exchange_t;


typedef struct _RingContext_Type_
{
	volatile uint8_t Head;
	volatile uint8_t Tail;
	uint8_t  Buffer[MAX_BUFFER_SIZE];
}RingContext_Type;


//const gpin_state pinsta[] =
//{
//		{GPIO_PIN_RESET,GPIO_PIN_RESET},
//		{GPIO_PIN_RESET,GPIO_PIN_SET},
//		{GPIO_PIN_SET,GPIO_PIN_RESET},
//		{GPIO_PIN_SET,GPIO_PIN_SET}
//};

#endif /* APPLICATION_USER_BOOTFUNCTION_INC_STD_TYPES_H_ */

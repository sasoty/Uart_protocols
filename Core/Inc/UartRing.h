/*
 * UartRing.h
 *
 *  Created on: Oct 29, 2022
 *      Author: ngocn
 */

#ifndef APPLICATION_USER_BOOTFUNCTION_INC_UARTRING_H_
#define APPLICATION_USER_BOOTFUNCTION_INC_UARTRING_H_
#include "Std_Types.h"
#include "main.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"


//#define MAX_BUFFER_SIZE 32



//typedef struct _RingContext_Type_
//{
//	volatile uint8_t Head;
//	volatile uint8_t Tail;
//	uint8_t  Buffer[MAX_BUFFER_SIZE];
//}RingContext_Type;

/**
 * Init Ring BUffer
 */
void RingBufferInit(void);
/*
 * Buffer Stuff from Resource , Rightnow is Uart
 */
void BufferStuff(uint8_t Data);

/**
 * Check if Data is available
 */
Std_Return RingData_Avail(void);

/**
 * Write Data to Buffer
 */
void UartRing_WriteBuf(uint8_t data);

/**
 * Read Buffer Out
 */
uint8_t ReadBuf(void);



void ResetBuf(void);

#endif /* APPLICATION_USER_BOOTFUNCTION_INC_UARTRING_H_ */

/*
 * Ring_cmd.h
 *
 *  Created on: May 20, 2023
 *      Author: Minh Nhat
 */

#ifndef INC_RING_CMD_H_
#define INC_RING_CMD_H_
#include "stdbool.h"
#include "stdio.h"
#include "Push_val.h"
#include "Get_val.h"

//#include "Get_val.h"


// uint8_t Rec_cmd(cmd_type input);

// uint8_t Rec_val();



typedef enum
{
    E_val_not_ok = 1,
    E_val_ok = 0
}Val_state;

typedef struct {
    float value;
    bool connected; 
    bool side; 
} ValueResult;


void num_of_tick();
void ERR_Handle(void);
void ACK_Handle(void);
void REQ_Handle(void);
void Bed_Connect();
Val_state Val_Avail();



#endif /* INC_RING_CMD_H_ */

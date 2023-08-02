/*
 * Ring_cmd.c
 *
 *  Created on: May 20, 2023
 *      Author: Minh Nhat
 */

/* send data but with 90milis timeout, div by 3 time*/
/*need function to tick every 30milis*/
/* CMD type, Request, ACK, no buffer*/
/*Tx for main, Rx for scale*/
/*if num*/

#include "Ring_cmd.h"
#include "stdbool.h"
#include "stdio.h"
#include "Std_Types.h"
//#include"Get_val.h"

volatile bool not_avail;

uint8_t time_out =0;

bool term = false;
ValueResult *Scale_t;
static int err_counter = 0;


void num_of_tick()
{
   /*check again before run*/
    if (term && (time_out < 10))
    {
        time_out++;
        if (time_out >= 10)
        {
            ERR_Handle();
        }
    }
    else
    {

    }
}


void ERR_Handle()
{
      // Counter variable

    // Increment the counter
    err_counter++;

    if (err_counter >= 3)
    {
        // Set the not_avail condition
        not_avail = true;
    }
    else
    {
        if(Scale_t->connected == false)
        {
            REQ_Handle();
        }
        else
        {
            ACK_Handle();
        }
    }

}

void ACK_Handle()
{
       if (Scale_t->side == true)
    {
        Push_cmd(VAL_);
        uint8_t temp2 = Type_ret();
        if(temp2 == TYPE1)
        {
            ERR_Handle();
        }

    }
    else
    {

        cmd_type temp = Get_cmd();
        if (temp == VAL_)
        {
 //           send_value();
        }
        else
        {
            ERR_Handle();
        }
    }
}

void REQ_Handle()
{
    if (Scale_t->side == true)
    {
    	Push_cmd(REQ_);
        cmd_type temp = Get_cmd();
        if (temp == ACK_)
        {
            Scale_t->connected = true;
        }
        else
        {
            ERR_Handle();
        }
    }
    else
    {
        cmd_type temp = Get_cmd();
        if (temp == REQ_)
        {
            Scale_t->connected = true;
        }
        else
        {
            ERR_Handle();
        }
    }
}



void Bed_Connect(ValueResult *Scale_temp)
{
	Scale_t = Scale_temp;
    term = false;
    while((!Scale_t->connected)&&(!not_avail))
    {
        REQ_Handle();
    }
    term = false;
    Scale_t->connected = false;

 //    Reset the counter


     // Check if the value is available
//     if (type_ret() == TYPE1)
//     {
//         return E_val_not_ok;
//     }
//     return E_val_ok;
}
Val_state Val_Avail(ValueResult *Scale_temp)
{
	Scale_t = Scale_temp;
    while(!not_avail)
    {
        term = true;
        ACK_Handle();
        return E_val_ok;
    }
       err_counter = 0;
    return E_val_not_ok;

}


// float VAL_Return()
// {
//     return Takeout();
// }


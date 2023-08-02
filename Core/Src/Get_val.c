/*
 * Get_val.c
 *
 *  Created on: Dec 30, 2022
 *      Author: Minh Nhat
 */


//#include "stdio.h"
//#include "stdbool.h"
#include "Get_val.h"
//#include "UartRing.h"

//-----------------------------------------------------------------------
    sta_read State_Rx = SOF_;
    uint8_t Type_Rx = 0;
    uint8_t Len_Rx = 0;
    uint8_t Crc_Rx =0;
    uint8_t Data_Rx = 0;
    uint8_t Chunk_Rx[16];
    uint8_t Frame_Rx[4];
    uint8_t Count_Rx=0;
    exchange_t Ret_Rx;
//    exchange_t *Pdata;


  //  Eror_Sta comsta = FAIL;

//-----------------------------------------------------------------------

void GetInit(void)
{
    State_Rx = SOF_;
//    Pdata = &Ret_Rx;
    Type_Rx = 0;
    Len_Rx = 0;
    Crc_Rx =0;
    Data_Rx = 0;
    Count_Rx=0;
 //   comsta = FAIL_ ;
}

//------------------------------------------------------------------------

sta_read GetData(void)
{
	Std_Return Avail = Rx_RingData_Avail();
	if(Avail == E_OK)
	{
     Data_Rx = Rx_ReadBuf();
        switch(State_Rx)
        {
          case SOF_:
            {
                if(Data_Rx == STX )
                {
                    State_Rx = TYP_;
                }
                else
                {
                    State_Rx = SOF_;
                }
                break;
            }
            case TYP_:
            {
                if(Data_Rx == TYPE1)
                {
                    Type_Rx = 0x02;
                    State_Rx = LEN_;
                }
                else if(Data_Rx == TYPE2)
                {
                    Type_Rx = 0x04;
                    State_Rx = LEN_;
                }
                else
                {
                    State_Rx = SOF_;
                }
                break;
            }
            case LEN_:
            {
                Len_Rx = Data_Rx;
                if(Len_Rx >= Type_Rx)
                {
                    if(Len_Rx >= 16)
                    {
                    	State_Rx = SOF_;
                    }
                    else
                    {
                	State_Rx = DATA_;}
                }

                else
                {
                	State_Rx = SOF_;
                }
                break;
            }
            case DATA_:
            {
                if(Count_Rx == Len_Rx-1)
                {
                    Chunk_Rx[Count_Rx]=Data_Rx;
                    State_Rx = CRC_;
                }
                else
                {
                    Chunk_Rx[Count_Rx]=Data_Rx;
                    Count_Rx++;
                }
                break;
            }
            case CRC_:
            {
                Crc_Rx = Data_Rx;
                State_Rx = EOF_;
                break;
            }
            case EOF_:
            {
            	break;
            }

        }
	}
	else
	{;}
    return State_Rx;
}

//---------------------------------------------------------------------------
void DecrypData (void)
{
    int i = 0;
    for(Count_Rx = 0; Count_Rx < Len_Rx; Count_Rx ++)
    {
        while(Chunk_Rx[Count_Rx] == FLG)
        {
            Count_Rx++;
            if(Chunk_Rx[Count_Rx]==0x06)
            {
                Chunk_Rx[Count_Rx]=0x01;
            }
            else if (Chunk_Rx[Count_Rx]==0x05)
            {
                Chunk_Rx[Count_Rx]=0x02;
            }
            else
            {
                Chunk_Rx[Count_Rx]=0x07;
            }

        }
        Frame_Rx[i]=Chunk_Rx[Count_Rx];
        i++;
    }
}

//----------------------------------------------------------------------------
//void EncrypData(void)
//{
//	int i =0;
//    for(Count_Rx = 0; Count_Rx < Type_Rx; Count_Rx++)
//    {
//        if(Frame_Rx[Count_Rx]==STX)
//        {
//            Chunk_Rx[i]=FLG;
//            i++;
//            Chunk_Rx[i]=0x06;
//        }
//        else if(Frame_Rx[Count_Rx]==ETX)
//        {
//            Chunk_Rx[i]=FLG;
//            i++;
//            Chunk_Rx[i]=0x05;
//        }
//        else if (Frame_Rx[Count_Rx] == FLG)
//        {
//            Chunk_Rx[i]=FLG;
//            i++;
//            Chunk_Rx[i]=FLG;
//        }
//        else
//        {
//            Chunk_Rx[i]=Frame_Rx[Count_Rx];
//        }
//        i++;
//
//
//        // switch(Frame_Rx[Count_Rx])
//        // {
//        //     case STX:
//
//        // }
//    }
//}

//------------------------------------------------------------------------------

float chunkSum(void)
{
    for(Count_Rx = 0;Count_Rx < Type_Rx; Count_Rx++ )
    {
        Ret_Rx.seg[Count_Rx] = Frame_Rx[Count_Rx];
    }
    return Ret_Rx.fl;
}

//----------------------------------------------------------------------------
float Takeout(void)
{

    DecrypData();

    float ret = chunkSum();

    return ret;
}
 //---------------------------------------------------------------------------

cmd_type Get_cmd()
{
    while(State_Rx < EOF_)
    {
    	GetData();
    }
    return Chunk_Rx[0];
}

//---------------------------------------------------------------------------------
uint8_t Type_ret(void)
{
    while(State_Rx < EOF_)
    {
    	GetData();

    }
    return Type_Rx;
}

//-----------------------------------------------------------------------------------
// void Takein(void)
// {
//     EncrypData();


// }


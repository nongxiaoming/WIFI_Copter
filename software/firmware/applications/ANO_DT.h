#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "config.h"
#include "ano_protocol.h"

struct Transmiter
{
u8 Send_Status;
u8 Send_Senser;
u8 Send_PID1;
u8 Send_PID2;
u8 Send_PID3;
u8 Send_RCData;
u8 Send_Offset;
u8 Send_MotoPwm;
};
void Transmiter_Data_Anl(u8 *data_buf,u8 num);
	//检查是否有接收到无线数据
void Transmiter_CheckEvent(void);
	//数据发送
void Transmiter_DataExchange(void);
	//失控保护检查
void Transmiter_FailsafeCheck(void);

extern struct Transmiter dt;

#endif










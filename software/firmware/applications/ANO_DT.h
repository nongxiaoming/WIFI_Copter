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
	//����Ƿ��н��յ���������
void Transmiter_CheckEvent(void);
	//���ݷ���
void Transmiter_DataExchange(void);
	//ʧ�ر������
void Transmiter_FailsafeCheck(void);

extern struct Transmiter dt;

#endif










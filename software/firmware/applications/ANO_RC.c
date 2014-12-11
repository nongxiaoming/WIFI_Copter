/************************ (C) COPYRIGHT 2014 ANO Tech ******************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_RC.cpp
 * ����    ��ң��ͨ�����ݴ���
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_RC.h"

struct Commander rc;


static 	int16_t lookupPitchRollRC[PITCH_LOOKUP_LENGTH];     
static	int16_t lookupThrottleRC[THROTTLE_LOOKUP_LENGTH]; 

const uint8_t stick_min_flag[4] = {1<<0,1<<2,1<<4,1<<6}; 
const uint8_t stick_max_flag[4] = {1<<1,1<<3,1<<5,1<<7};
#define ROL_L 0x01
#define ROL_H 0x02
#define PIT_L	0x04
#define PIT_H 0x08
#define YAW_L 0x10
#define YAW_H 0x20
#define THR_L 0x40
#define THR_H 0x80

void Commander_Cal(void)
{
 	u8 i=0;
	
    for (i = 0; i < 3; i++) 
		{	//����ROLL,PITCH,YAW�������������
			rc.Command[i] = (rc.rawData[i] - RC_MID) * 0.25;
		}
		rc.Command[YAW] = -rc.Command[YAW];
		rc.Command[THROTTLE] = rc.rawData[THROTTLE];
		
}

void Commander_CheckSticks(void)
{
	int i;
	static uint8_t rcDelayCommand;
	
	static uint8_t stick_flag = 0;

	for (i = 0; i < 4; i++) 
	{
			if(rc.rawData[i]<900||rc.rawData[i]>2000)	//���ҡ��ֵ����������Χ�ڣ����˳����
				break;
			
			if (rc.rawData[i] < RC_MINCHECK)
					stick_flag |= stick_min_flag[i];  // check for MIN
			else if (rc.rawData[i] > RC_MAXCHECK)
					stick_flag |= stick_max_flag[i];  // check for MAX
	}	
	
	if(stick_flag&0xff)	//�����һҡ����������Сλ��
	{
		if(rcDelayCommand < 250)
			rcDelayCommand++;
	}
	else
	{
		rcDelayCommand = 0;
		stick_flag &= 0;
	}	
	
	if (rcDelayCommand == 100) //2s: 20ms * 100
	{
		if (config.ARMED) //����Ѿ����ڽ���״̬
		{ 
			if((stick_flag & YAW_L)&&(stick_flag & THR_L))
			{
				config.ARMED = 0;	//����
			}
		}
		else
		{
			if((stick_flag & YAW_H)&&(stick_flag & THR_L))
			{
				config.ARMED = 1;	//����
			}
		}
		stick_flag &= 0;
		rcDelayCommand = 0;
	}
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
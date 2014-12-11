/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_Config.cpp
 * ����    �������ļ�
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/

#include "ANO_Config.h"

ANO_Config ano;


ANO_Config::ANO_Config(void)
{
	
}

//ָʾ��
void ANO_Config::Pilot_Light(void)
{
	static u8 cnt = 0;
	
	if(f.ARMED)
	{
		cnt++;
		switch(cnt)
		{
			case 1:
				LED_ON();
				break;
			case 25:
				LED_OFF();
				break;
			case 50:
				cnt = 0;
				break;
		}
	}
	else
	{
		LED_ON(); 
	}
	
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

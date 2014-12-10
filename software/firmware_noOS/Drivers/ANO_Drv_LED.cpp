/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_Drv_LED.cpp
 * ����    ��LED
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "ANO_Drv_LED.h"

ANO_LED led;

void ANO_LED::Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(ANO_RCC_LED,ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED;
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
}

void ANO_LED::ON(void)
{
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED);	
}

void ANO_LED::OFF(void)
{
	GPIO_SetBits(ANO_GPIO_LED, ANO_Pin_LED);		
}




/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/


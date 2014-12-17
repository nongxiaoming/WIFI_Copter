/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��AnoCopter.cpp
 * ����    ������΢�����������
 * ����汾��V1.0
 * ʱ��		 ��2014/10/13 
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "config.h"
#include "params.h"

int main(void)
{
	//��ʼ���ɿذ��Ӳ������
	board_Init();
	
	//��ʼ��IMU�����Բ�����Ԫ��
	IMU_Init();	
	
	//��ʼ������
	Params_Init();
	
	//��ʼ��TCPServer
	tcpserver_init();
	
	//��ʼ��������
	Scheduler_Init();
	
	while(1)
	{
		Scheduler_Run();
	}
	
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

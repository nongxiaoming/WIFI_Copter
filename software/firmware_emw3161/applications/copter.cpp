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
	imu.Init();	
	
	//��ʼ������
	Params_Init();
	
	//��ʼ��TCPServer
	tcpserver_init();
	
	while(1)
	{
		ANO_Loop();
	}
	
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

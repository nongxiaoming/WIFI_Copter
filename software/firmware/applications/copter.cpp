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
#include "ANO_Config.h"
#include "params.h"
#include "pidctrl.h"


//static void rt_init_thread_entry(void* parameter)
//{
//	//����Ƿ��н��յ���������
//	dt.Check_Event();
//	rt_thread_delay(1);
//}

static void attitude_thread_entry(void* parameter)
{	
	while(1){
	//���´���������	
	imu.updateSensor();		
	
	//�����������̬
	imu.getAttitude();
	
	//��������̬����
	pidctrl.Attitude();
	
  rt_thread_delay(2);	
	}
}

static void data_transmit_thread_entry(void* parameter)
{
	while(1){
	//���ͷ���������
	dt.Data_Exchange();
	rt_thread_delay(10);
	}	
}

static void receiver_thread_entry(void* parameter)
{
	while(1){
	//ң��ͨ�����ݴ���
	rc.Cal_Command();
	
	//ҡ��λ�ü��
	rc.check_sticks();
	
	//ʧ�ر������
	dt.Failsafe_Check();
	
	rt_thread_delay(20);	
	}
}

int apps_copter_init(void)
{
  rt_thread_t attitude_thread,data_transmit_thread,receiver_thread;
	//��ʼ������
	params.Init();
	
	//��ʼ��IMU�����Բ�����Ԫ��
	imu.Init();	
	
	//��ʼ��pid����
	pidctrl.Init();

	attitude_thread = rt_thread_create("attitude",attitude_thread_entry,RT_NULL,1024,12,5);
	if(attitude_thread != RT_NULL)
	{
		rt_thread_startup(attitude_thread);
	}
	data_transmit_thread = rt_thread_create("transmit",data_transmit_thread_entry,RT_NULL,1024,13,5);
	if(data_transmit_thread != RT_NULL)
	{
		rt_thread_startup(data_transmit_thread);
	}
		receiver_thread = rt_thread_create("transmit",receiver_thread_entry,RT_NULL,1024,14,5);
	if(receiver_thread != RT_NULL)
	{
		rt_thread_startup(receiver_thread);
	}
	return 0;
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
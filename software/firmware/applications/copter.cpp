/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：AnoCopter.cpp
 * 描述    ：匿名微型六轴飞行器
 * 代码版本：V1.0
 * 时间		 ：2014/10/13 
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_Config.h"
#include "params.h"
#include "pidctrl.h"


//static void rt_init_thread_entry(void* parameter)
//{
//	//检查是否有接收到无线数据
//	dt.Check_Event();
//	rt_thread_delay(1);
//}

static void attitude_thread_entry(void* parameter)
{	
	//更新传感器数据	
	imu.updateSensor();		
	
	//计算飞行器姿态
	imu.getAttitude();
	
	//飞行器姿态控制
	pidctrl.Attitude();
	
  rt_thread_delay(2);	
}

static void data_transmit_thread_entry(void* parameter)
{
	//发送飞行器数据
	dt.Data_Exchange();
	rt_thread_delay(10);	
}

static void receiver_thread_entry(void* parameter)
{
	//遥控通道数据处理
	rc.Cal_Command();
	
	//摇杆位置检查
	rc.check_sticks();
	
	//失控保护检查
	dt.Failsafe_Check();
	
	rt_thread_delay(20);	
}

int apps_copter_init(void)
{
  rt_thread_t attitude_thread,data_transmit_thread,receiver_thread;
	//初始化参数
	params.Init();
	
	//初始化IMU（惯性测量单元）
	imu.Init();	
	
	//初始化pid控制
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

#include <stdio.h>
#include "stm32f2xx.h"
#include <rtthread.h>
#include "sysconfig.h"
#include "mpu6050.h"
#include "imu.h"
#include "control.h"
#include "data_transfer.h"

struct rt_event Evt_Sys;
T_int16_xyz		GYRO_OFFSET,ACC_OFFSET;			
static u8				mpu6050_buffer[14];					//iic读取后存放数据
static u8				GYRO_OFFSET_OK = 1;
static u8				ACC_OFFSET_OK = 1;
T_int16_xyz 	Acc,Gyr;	//两次综合后的传感器数据
rt_device_t mpu6050_dev = RT_NULL;
void MPU6050_CalOff_Acc(void)
{
	ACC_OFFSET_OK = 0;
}
void MPU6050_CalOff_Gyr(void)
{
	GYRO_OFFSET_OK = 0;
}

/**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器
*******************************************************************************/
#define 	MPU6050_MAX		32767
#define		MPU6050_MIN		-32768
void MPU6050_Dataanl(T_int16_xyz *data_tempacc,T_int16_xyz *data_tempgyr)
{
	vs32 acc_x,acc_y,acc_z,gyr_x,gyr_y,gyr_z;
	
	acc_x=((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - ACC_OFFSET.X;
	acc_y=((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - ACC_OFFSET.Y;
	acc_z=((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]) - ACC_OFFSET.Z;
	//跳过温度ADC
	gyr_x=((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]) - GYRO_OFFSET.X;
	gyr_y=((((int16_t)mpu6050_buffer[10]) << 8) | mpu6050_buffer[11]) - GYRO_OFFSET.Y;
	gyr_z=((((int16_t)mpu6050_buffer[12]) << 8) | mpu6050_buffer[13]) - GYRO_OFFSET.Z;
	
//	acc_x=acc_x>MPU6050_MAX ? MPU6050_MAX:acc_x;
//	acc_x=acc_x<MPU6050_MIN ? MPU6050_MIN:acc_x;
//	acc_y=acc_y>MPU6050_MAX ? MPU6050_MAX:acc_y;
//	acc_y=acc_y<MPU6050_MIN ? MPU6050_MIN:acc_y;
//	acc_z>MPU6050_MAX ? MPU6050_MAX:acc_z;
//	acc_z<MPU6050_MIN ? MPU6050_MIN:acc_z;
//	gyr_x>MPU6050_MAX ? MPU6050_MAX:gyr_x;
//	gyr_x<MPU6050_MIN ? MPU6050_MIN:gyr_x;
//	gyr_y>MPU6050_MAX ? MPU6050_MAX:gyr_y;
//	gyr_y<MPU6050_MIN ? MPU6050_MIN:gyr_y;
//	gyr_z>MPU6050_MAX ? MPU6050_MAX:gyr_z;
//	gyr_z<MPU6050_MIN ? MPU6050_MIN:gyr_z;
	
	data_tempacc->X = acc_x;
	data_tempacc->Y = acc_y;
	data_tempacc->Z = acc_z;
	data_tempgyr->X = gyr_x;
	data_tempgyr->Y = gyr_y;
	data_tempgyr->Z = gyr_z;
	
	if(!GYRO_OFFSET_OK)
	{
		static int32_t	tempgx=0,tempgy=0,tempgz=0;
		static uint8_t cnt_g=0;
// 		LED1_ON;
		if(cnt_g==0)
		{
			GYRO_OFFSET.X=0;
			GYRO_OFFSET.Y=0;
			GYRO_OFFSET.Z=0;
			tempgx = 0;
			tempgy = 0;
			tempgz = 0;
			cnt_g = 1;
			return;
		}
		tempgx+= data_tempgyr->X;
		tempgy+= data_tempgyr->Y;
		tempgz+= data_tempgyr->Z;
		if(cnt_g==200)
		{
			GYRO_OFFSET.X=tempgx/cnt_g;
			GYRO_OFFSET.Y=tempgy/cnt_g;
			GYRO_OFFSET.Z=tempgz/cnt_g;
			cnt_g = 0;
			GYRO_OFFSET_OK = 1;
//			Data_Save();
			return;
		}
		cnt_g++;
	}
	if(!ACC_OFFSET_OK)
	{
		static int32_t	tempax=0,tempay=0,tempaz=0;
		static uint8_t cnt_a=0;
// 		LED1_ON;
		if(cnt_a==0)
		{
			ACC_OFFSET.X = 0;
			ACC_OFFSET.Y = 0;
			ACC_OFFSET.Z = 0;
			tempax = 0;
			tempay = 0;
			tempaz = 0;
			cnt_a = 1;
			return;
		}
		tempax+= data_tempacc->X;
		tempay+= data_tempacc->Y;
		//tempaz+= MPU6050_ACC_LAST.Z;
		if(cnt_a==200)
		{
			ACC_OFFSET.X=tempax/cnt_a;
			ACC_OFFSET.Y=tempay/cnt_a;
			ACC_OFFSET.Z=tempaz/cnt_a;
			cnt_a = 0;
			ACC_OFFSET_OK = 1;
///			Data_Save();
			return;
		}
		cnt_a++;		
	}
}

ALIGN(RT_ALIGN_SIZE)
char thread_6050_stack[1024];
struct rt_thread thd_6050;
void rt_thread_entry_6050(void* parameter)
{
	static rt_uint32_t ev;
	static T_int16_xyz mpu6050_dataacc1,mpu6050_dataacc2,mpu6050_datagyr1,mpu6050_datagyr2;
	static u8 d_6050_sta = 0;
	mpu6050_dev = rt_device_find("mpu6050");
	if(mpu6050_dev==RT_NULL)
  {
	 rt_kprintf("can not find mpu6050!\n");
	 return;
	}
	rt_device_open(mpu6050_dev,RT_DEVICE_FLAG_RDWR);
	
	while(1)
	{
		rt_event_recv(&Evt_Sys,EVT_SS_6050,RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&ev);
		rt_device_read(mpu6050_dev,MPU6050_RA_ACCEL_XOUT_H,mpu6050_buffer,14);
		d_6050_sta++;
		if(d_6050_sta==1)
			MPU6050_Dataanl(&mpu6050_dataacc1,&mpu6050_datagyr1);
		else
		{
			d_6050_sta = 0;
			MPU6050_Dataanl(&mpu6050_dataacc2,&mpu6050_datagyr2);
			Acc.X = (mpu6050_dataacc1.X+mpu6050_dataacc2.X)/2;
			Acc.Y = (mpu6050_dataacc1.Y+mpu6050_dataacc2.Y)/2;
			Acc.Z = (mpu6050_dataacc1.Z+mpu6050_dataacc2.Z)/2;
			Gyr.X = (mpu6050_datagyr1.X+mpu6050_datagyr2.X)/2;
			Gyr.Y = (mpu6050_datagyr1.Y+mpu6050_datagyr2.Y)/2;
			Gyr.Z = (mpu6050_datagyr1.Z+mpu6050_datagyr2.Z)/2;
			rt_event_send(&Evt_Sys,EVT_CL_ATT);
		}
		//rt_thread_delay(2);
	}
}
/******************************************************************************/
//ATT线程,2ms一次
//姿态算法进程,只接收6050与8975的数据,进行当前姿态计算,输出rol,pit,yaw三个角度
T_int16_xyz		Acc_AVG;	
T_int16_xyz		Mag;
vs32			Alt;
T_float_angle 	Att_Angle;	//ATT函数计算出的姿态角
float			Mag_Heading;
/******************************************************************************/
ALIGN(RT_ALIGN_SIZE)
char thread_ATT_stack[1024];
struct rt_thread thd_ATT;
void rt_thread_entry_ATT(void* parameter)		
{
	static rt_uint32_t ev;

	PID_ROL.P = 13;
	PID_PIT.P = PID_ROL.P;
	
	PID_ROL.I = 0.005;
	PID_PIT.I = PID_ROL.I;
	
	PID_ROL.D = 0.15;
	PID_PIT.D = PID_ROL.D;
	
	PID_YAW.P = 5;
	PID_YAW.I = 0;
	PID_YAW.D = 0.06;
	
	MPU6050_CalOff_Acc();
	MPU6050_CalOff_Gyr();
	
	while(1)
	{
		rt_event_recv(&Evt_Sys,EVT_CL_ATT,RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&ev);
		Prepare_Data(&Acc,&Acc_AVG);
		IMUupdate(&Gyr,&Acc_AVG,&Att_Angle);
		Control(&Att_Angle,&Gyr,&Rc_D,RC_Control.ARMED);
	}
}
	/******************************************************************************/
//RC线程
T_RC_Data 		Rc_D;
T_Control		RC_Control;
/******************************************************************************/
ALIGN(RT_ALIGN_SIZE)
char thread_RC_stack[1024];
struct rt_thread thd_RC;
void rt_thread_entry_RC(void* parameter)		
{
	rt_uint32_t ev;
	static u8 cal_flag = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	while(1)
	{
		if(rt_event_recv(&Evt_Sys,EVT_GET_RC,RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,500,&ev)==0)
		{
			if(RC_Control.ARMED ==0 && cal_flag ==0 && Rc_D.AUX1>1800)
			{
				cal_flag = 1;
				MPU6050_CalOff_Acc();
				MPU6050_CalOff_Gyr();
			}
			if(RC_Control.ARMED ==0 && cal_flag ==1 && Rc_D.AUX1<1800)
			{
				cal_flag = 0;
			}
		}
		else
		{
			RC_Control.ARMED = 0;
		}
		if(RC_Control.ARMED)
			GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		else
			GPIO_SetBits(GPIOF,GPIO_Pin_9);
	}

}
/******************************************************************************/
//DATA_TRANSFER线程
/******************************************************************************/
ALIGN(RT_ALIGN_SIZE)
char thread_DataTrans_stack[1024];
struct rt_thread thd_DataTrans;
void rt_thread_entry_DataTrans(void* parameter)		
{
	//static rt_uint32_t ev;

	while(1)
	{
			Data_Send_Status();
			Data_Send_Senser();
			Data_Send_RCData();
			Data_Send_MotoPWM();
		rt_thread_delay(10);
	}
}

void rt_copter_apps_init()
{
		rt_err_t resault;
	resault = rt_event_init(&Evt_Sys,"Evt_Senser",RT_IPC_FLAG_FIFO);
	if(resault != RT_EOK)	return;
  //------- 
    rt_thread_init(&thd_6050,
                   "6050",
                   rt_thread_entry_6050,
                   RT_NULL,
                   &thread_6050_stack[0],
                   sizeof(thread_6050_stack),THD_6050_P,5);
    rt_thread_startup(&thd_6050);
		
	//------- 
    rt_thread_init(&thd_ATT,
                   "ATT",
                   rt_thread_entry_ATT,
                   RT_NULL,
                   &thread_ATT_stack[0],
                   sizeof(thread_ATT_stack),THD_ATT_P,5);
    rt_thread_startup(&thd_ATT);
	
	//------- 
    rt_thread_init(&thd_RC,
                   "RC",
                   rt_thread_entry_RC,
                   RT_NULL,
                   &thread_RC_stack[0],
                   sizeof(thread_RC_stack),THD_RC_P,5);
    rt_thread_startup(&thd_RC);

		//------- 
    rt_thread_init(&thd_DataTrans,
                   "DT",
                   rt_thread_entry_DataTrans,
                   RT_NULL,
                   &thread_DataTrans_stack[0],
                   sizeof(thread_DataTrans_stack),THD_DT_P,5);
    rt_thread_startup(&thd_DataTrans);
}

#ifndef __SYSCONFIG_H__
#define __SYSCONFIG_H__
#include <rtthread.h>
#include "stm32f2xx.h"

#define NVIC_SYSTIMER_P			4
#define NVIC_SYSTIMER_S			1

#define NVIC_UART1_P			5
#define NVIC_UART1_S			1

//信号量
#define EVT_SS_6050				1
#define EVT_CL_ATT				(1<<3)
#define EVT_GET_RC				(1<<5)
#define EVT_JPEGGET				(1<<10)
//系统线程优先级
#define THD_6050_P			1
#define THD_ATT_P				2
#define THD_RC_P				4
#define THD_DT_P				5
#define THD_LED_P				30
#define THD_WIFI_P			15

typedef struct{
				float rol;
				float pit;
				float yaw;}T_float_angle;
typedef struct{
				float X;
				float Y;
				float Z;}T_float_xyz;
typedef struct{
				int16_t X;
				int16_t Y;
				int16_t Z;}T_int16_xyz;
typedef struct int16_rcget{
				int16_t ROLL;
				int16_t PITCH;
				int16_t THROTTLE;
				int16_t YAW;
				int16_t AUX1;
				int16_t AUX2;
				int16_t AUX3;
				int16_t AUX4;
				int16_t AUX5;
				int16_t AUX6;}T_RC_Data;
typedef struct{
				u8		ARMED;	//=0,锁定
				}T_Control;
				
extern char thread_6050_stack[1024];
extern struct rt_thread thd_6050;
void rt_thread_entry_6050(void* parameter);

extern char thread_ATT_stack[1024];
extern struct rt_thread thd_ATT;
void rt_thread_entry_ATT(void* parameter);
				
extern char thread_DataTrans_stack[1024];
extern struct rt_thread thd_DataTrans;
void rt_thread_entry_DataTrans(void* parameter);
				
extern char thread_RC_stack[1024];
extern struct rt_thread thd_RC;
void rt_thread_entry_RC(void* parameter);

extern char thread_Video_stack[1024];
extern struct rt_thread thd_Video;
void rt_thread_entry_Video(void* parameter);

#define RC_FUN_MIN	1200
#define RC_FUN_MAX	1800

extern struct rt_event Evt_Sys;		//飞控相关信号量
				
extern T_int16_xyz 		Acc,Gyr;	//两次综合后的传感器数据
extern T_float_angle 	Att_Angle;	//ATT函数计算出的姿态角
extern T_RC_Data 		Rc_D;
extern T_Control		RC_Control;

extern u8 JpegDma_BufNum, JpegSend_State;

#endif

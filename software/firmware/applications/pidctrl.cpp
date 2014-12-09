/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_FlyControl.cpp
 * 描述    ：飞行控制
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "pidctrl.h"
#include "sensor.h"

struct PID pid_group[PIDITEMS];

static void PIDGroup_Reset(void);
static void MotorCtrl(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw);
static rt_device_t moto_dev=RT_NULL;
static uint16_t motorPWM[4];


void PIDCtrl_Init(void)
{
	//重置PID参数
	PIDGroup_Reset();
  moto_dev = rt_device_find("motors");
	 if(moto_dev == RT_NULL)
   {
	  rt_kprintf("can not found motors device!\n");
		 return ;
	 }
	 rt_device_open(moto_dev,RT_DEVICE_FLAG_RDWR);
}
//重置PID参数
static void PIDGroup_Reset(void)
{
	PID_SET_VALUE(&pid_group[PIDROLL],55, 25, 65, 2000000);
	PID_SET_VALUE(&pid_group[PIDPITCH],55, 25, 65, 2000000);
	PID_SET_VALUE(&pid_group[PIDYAW],50, 50, 0, 2000000);
}

//飞行器姿态控制
void PIDCtrl_Attitude(void)
{
	int32_t PIDTerm[3];
	int32_t	errorAngle[3];
	
	//计算角度误差值
	errorAngle[ROLL] = constrain_int32((rc.Command[ROLL] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.x * 10; 
	errorAngle[PITCH] = constrain_int32((rc.Command[PITCH] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.y * 10; 
	errorAngle[YAW] = rc.Command[YAW] * 5 - Sensor_GetGyro().z / 4;	
	
	for(u8 i=0; i<3;i++)
	{
		//当油门低于检查值时积分清零
		if ((rc.rawData[THROTTLE]) < RC_MINCHECK)
			{	
			PID_RESET_I(pid_group[i]);
			}
		
		//得到PID输出
		PIDTerm[i] = PID_GET_PID(&pid_group[i],errorAngle[i], PID_LOOP_TIME);
	}
	
	PIDTerm[YAW] = -constrain_int32(PIDTerm[YAW], -300 - abs(rc.Command[YAW]), +300 + abs(rc.Command[YAW]));		
	
	//PID输出转为电机控制量
	MotorCtrl(rc.Command[THROTTLE], PIDTerm[ROLL], PIDTerm[PITCH], PIDTerm[YAW]);
}
static void MotorCtrl(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw)
{
	//六轴X型
	motorPWM[0] = throttle - 0.5 * pidTermRoll + 0.866 *  pidTermPitch + pidTermYaw; //后右
	motorPWM[1] = throttle - 0.5 * pidTermRoll - 0.866 *  pidTermPitch + pidTermYaw; //前右
	motorPWM[2] = throttle + 0.5 * pidTermRoll + 0.866 *  pidTermPitch - pidTermYaw; //后左
	motorPWM[3] = throttle + 0.5 * pidTermRoll - 0.866 *  pidTermPitch - pidTermYaw; //前左

				
	for (u8 i = 0; i < 6; i++) 
		motorPWM[i] = constrain_uint16(motorPWM[i], MINTHROTTLE, MAXTHROTTLE);

	//如果未解锁，则将电机输出设置为最低
	if(!ano.f.ARMED || rc.rawData[THROTTLE] < 1200)	
		for(u8 i=0; i< 4 ; i++)
			motorPWM[i] = 1000;

	//写入电机PWM
	if(moto_dev != RT_NULL)
  {
  rt_device_write(moto_dev,0,motorPWM,4);
	}
	
}
void PIDCtrl_GetPWM(uint16_t* pwm)
{
	pwm[0] = motorPWM[0];
	pwm[1] = motorPWM[1];
	pwm[2] = motorPWM[2];
	pwm[3] = motorPWM[3];
}
/************************ (C) COPYRIGHT 2014 ANO TECH *****END OF FILE**********************/

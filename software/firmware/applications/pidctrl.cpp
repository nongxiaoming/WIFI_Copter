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

PIDCtrl pidctrl;


PIDCtrl::PIDCtrl()
{
	//重置PID参数
	PID_Reset();
}

//重置PID参数
void PIDCtrl::PID_Reset(void)
{
	pid[PIDROLL].set_pid(55, 25, 65, 2000000);
	pid[PIDPITCH].set_pid(55, 25, 65, 2000000);
	pid[PIDYAW].set_pid(50, 50, 0, 2000000);
}

//飞行器姿态控制
void PIDCtrl::Attitude_Loop(void)
{
	int32_t PIDTerm[3];
	int32_t	errorAngle[3];
	
	//计算角度误差值
	errorAngle[ROLL] = constrain_int32((rc.Command[ROLL] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.x * 10; 
	errorAngle[PITCH] = constrain_int32((rc.Command[PITCH] * 2) , -((int)FLYANGLE_MAX), +FLYANGLE_MAX) - imu.angle.y * 10; 
	errorAngle[YAW] = rc.Command[YAW] * 5 - sensor.Get_Gyro().z / 4;	
	
	for(u8 i=0; i<3;i++)
	{
		//当油门低于检查值时积分清零
		if ((rc.rawData[THROTTLE]) < RC_MINCHECK)	
			pid[i].reset_I();
		
		//得到PID输出
		PIDTerm[i] = pid[i].get_pid(errorAngle[i], PID_LOOP_TIME);
	}
	
	PIDTerm[YAW] = -constrain_int32(PIDTerm[YAW], -300 - abs(rc.Command[YAW]), +300 + abs(rc.Command[YAW]));		
	
	//PID输出转为电机控制量
	MotorCtrl(rc.Command[THROTTLE], PIDTerm[ROLL], PIDTerm[PITCH], PIDTerm[YAW]);
}
void PIDCtrl::MotorCtrl(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw)
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
	//pwm.SetPwm(motorPWM);
	
}
void PIDCtrl::getPWM(uint16_t* pwm)
{
	*(pwm) = motorPWM[0];
	*(pwm+1) = motorPWM[1];
	*(pwm+2) = motorPWM[2];
	*(pwm+3) = motorPWM[3];
}
/************************ (C) COPYRIGHT 2014 ANO TECH *****END OF FILE**********************/

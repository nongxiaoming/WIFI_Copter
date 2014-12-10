/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��pid.cpp
 * ����    ��PID�����
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "pid.h"


void PID_SET_VALUE(struct PID *pid,const uint16_t p,
									 const uint16_t i,
									 const uint16_t d,
									 const uint32_t  imaxval) {
			pid->kp = p; pid->ki = i; pid->kd = d; pid->imax = imaxval;
	}


int32_t PID_GET_I(struct PID *pid,int32_t error, uint16_t dt)
{
    if((pid->ki != 0) && (dt != 0)) {
        pid->integrator += (error * dt / 2048 ) * pid->ki;
				//�����޷�
				pid->integrator = constrain_int32(pid->integrator, -pid->imax, +pid->imax);		
				
        return pid->integrator / 8192;
    }
    return 0;
}


int32_t PID_GET_D(struct PID *pid,int32_t error, uint16_t dt)
{
    if ((pid->kd != 0) && (dt != 0)) {			
			int32_t derivative;
			derivative = error - pid->last_error; 
			pid->last_error = error;
			derivative = (derivative * ((uint16_t)0xFFFF / (dt / 16 ))) / 64;
			return (derivative * pid->kd) / 4;
    }
    return 0;
}

int32_t PID_GET_PI(struct PID *pid,int32_t error, uint16_t dt)
{
    return PID_GET_P(pid,error) + PID_GET_I(pid,error, dt);
}

int32_t PID_GET_PID(struct PID *pid,int32_t error, uint16_t dt)
{
    return PID_GET_P(pid,error) + PID_GET_I(pid,error, dt) + PID_GET_D(pid,error, dt);
}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

#ifndef __PID_H
#define __PID_H

#include <stdint.h>
#include "ANO_Math.h"
#include "params.h"


#define PID_INIT(pid) (pid).kp=0;\
                      (pid).ki=0;\
                      (pid).kd=0;\
                      (pid).imax=0
											
#define PID_GET_P(pid,err) (((int32_t)error) * (pid)->kp / 64)

#define PID_RESET_I(pid) (pid).integrator = 0

struct PID
{
	//PID参数
  uint16_t kp;
	uint16_t ki;
	uint16_t kd;
	
	//积分上限
	uint32_t imax;
	//积分器的值
	int32_t integrator; 
	//上一次的误差输入
	int32_t last_error;
};

void PID_SET_VALUE(struct PID *pid,const uint16_t p,
									 const uint16_t i,
									 const uint16_t d,
									 const uint32_t  imaxval);
//返回PID计算的值
int32_t PID_GET_PID(struct PID *pid,int32_t error, uint16_t dt);
int32_t PID_GET_PI(struct PID *pid,int32_t error, uint16_t dt);

int32_t PID_GET_I(struct PID *pid,int32_t error, uint16_t dt);
int32_t PID_GET_D(struct PID *pid,int32_t error, uint16_t dt);
	

	

	

#endif


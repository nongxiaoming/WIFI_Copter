#ifndef __PID_H
#define __PID_H

#include <stdint.h>
#include "ANO_Math.h"
#include "params.h"



class PID
{
	
public:
	
	PID(){
		value.kp = value.ki = value.kd = 0;
		imax = 0;
	}

	//PID参数
  rt_pid_t value;
	
	//返回PID计算的值
	int32_t get_pid(int32_t error, uint16_t dt);
	int32_t get_pi(int32_t error, uint16_t dt);
	int32_t get_p(int32_t error);
	int32_t get_i(int32_t error, uint16_t dt);
	int32_t get_d(int32_t error, uint16_t dt);
	
	//积分控制器的值清零
	void reset_I(void);
	
	void set_pid(const uint16_t p,
									 const uint16_t i,
									 const uint16_t d,
									 const uint32_t  imaxval) {
			value.kp = p; value.ki = i; value.kd = d; imax = imaxval;
	}
	
private:
	
	//积分上限
	uint32_t imax;
	//积分器的值
	int32_t integrator; 
	//上一次的误差输入
	int32_t last_error;
};



#endif


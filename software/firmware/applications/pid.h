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

	//PID����
  rt_pid_t value;
	
	//����PID�����ֵ
	int32_t get_pid(int32_t error, uint16_t dt);
	int32_t get_pi(int32_t error, uint16_t dt);
	int32_t get_p(int32_t error);
	int32_t get_i(int32_t error, uint16_t dt);
	int32_t get_d(int32_t error, uint16_t dt);
	
	//���ֿ�������ֵ����
	void reset_I(void);
	
	void set_pid(const uint16_t p,
									 const uint16_t i,
									 const uint16_t d,
									 const uint32_t  imaxval) {
			value.kp = p; value.ki = i; value.kd = d; imax = imaxval;
	}
	
private:
	
	//��������
	uint32_t imax;
	//��������ֵ
	int32_t integrator; 
	//��һ�ε��������
	int32_t last_error;
};



#endif


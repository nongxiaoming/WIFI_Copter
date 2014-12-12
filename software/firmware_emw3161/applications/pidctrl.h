#ifndef __PIDCTRL_H
#define __PIDCTRL_H

#include "pid.h"
#include "drv_motors.h"

#define FLYANGLE_MAX 250   //���������25��
#define THROTTLE_MIN 1100  //������Сֵ
#define THROTTLE_MAX 1900  //�������ֵ

enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
    PIDALT,
    PIDLEVEL,
    PIDMAG,
		PIDITEMS
};

class pidctrl
{

public:
	
	PID pid_group[PIDITEMS];

	pidctrl();

	//��̬�⻷����
	void Attitude_Outter_Loop(void);

	//��̬�ڻ�����
	void Attitude_Inner_Loop(void);
	
  //��ȡ���PWMֵ
  void getMotorsPWM(uint16_t* pwm);
private:
	
	uint8_t yawRate;
	int32_t RateError[3];
  uint16_t motorPWM[4];	
	void PID_Reset(void);
  void Motors_Ctrl(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw);
};

extern pidctrl fc;

#endif
























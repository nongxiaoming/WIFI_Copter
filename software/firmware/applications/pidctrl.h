#ifndef __PIDCTRL_H
#define __PIDCTRL_H

#include "ANO_Config.h"
#include "pid.h"
#include "rtthread.h"

#define FLYANGLE_MAX 250  //最大飞行倾角25度
#define MINTHROTTLE 1100
#define MAXTHROTTLE 1900

enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
		PIDITEMS
};

class PIDCtrl
{

public:
	
	PID pid[PIDITEMS];

	PIDCtrl();
  void Init(void);

  void getPWM(uint16_t* pwm);
	//姿态控制
	void Attitude(void);
	
private:
	void PID_Reset(void);
  void MotorCtrl(uint16_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw);
  rt_device_t moto_dev;
  uint16_t motorPWM[4];
};

extern PIDCtrl pidctrl;

#endif
























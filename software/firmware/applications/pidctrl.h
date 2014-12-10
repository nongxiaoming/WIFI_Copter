#ifndef __PIDCTRL_H
#define __PIDCTRL_H

#include "config.h"
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

extern struct PID pid_group[PIDITEMS];

void PIDCtrl_Init(void);

void PIDCtrl_GetPWM(uint16_t* pwm);

	//姿态控制
void PIDCtrl_Attitude(void);


#endif
























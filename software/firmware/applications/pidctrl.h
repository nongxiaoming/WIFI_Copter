#ifndef __PIDCTRL_H
#define __PIDCTRL_H

#include "ANO_Config.h"

#define FLYANGLE_MAX 250  //最大飞行倾角25度

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

	//姿态控制
	void Attitude_Loop(void);
	
private:
	
	void PID_Reset(void);
};

extern PIDCtrl pidctrl;

#endif
























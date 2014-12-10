#ifndef __ANO_RC_H
#define __ANO_RC_H

#include "config.h"

#define RC_MID  			1500                     
#define RC_MINCHECK		1150                      
#define RC_MAXCHECK  	1800 
#define RC_RATE  			50
#define RC_EXPO  			65
#define THR_MID  			50
#define THR_EXPO 			0		

#define PITCH_LOOKUP_LENGTH 7
#define THROTTLE_LOOKUP_LENGTH 12

enum {
    ROLL = 0,
    PITCH,
    YAW,
    THROTTLE,
    AUX1,
    AUX2,
    AUX3,
    AUX4
};

struct Commander
{
	uint16_t rawData[8];
	int16_t Command[4];
};

	//遥控通道数据处理
void Commander_Cal(void);
	//摇杆位置检测
void Commander_CheckSticks(void);

extern struct Commander rc;

#endif




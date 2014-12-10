#ifndef __IMU_H
#define __IMU_H

#include "config.h"

struct IMU 
{

	//欧拉角表示的飞行器姿态
	vector3f_t angle;
	
	vector3f_t Gyro, Acc, Acc_lpf_1st, Acc_lpf_2nd; 
	
};
void IMU_Init(void);
	
	//更新传感器数据
void IMU_UpdateSensor(void);	
	
	//计算飞行器姿态
void IMU_GetAttitude(void);
extern struct IMU  imu;

#endif


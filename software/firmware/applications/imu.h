#ifndef __IMU_H
#define __IMU_H

#include "config.h"

struct IMU 
{

	//欧拉角表示的飞行器姿态
	Vector3f angle;
	
	Vector3f Gyro, Acc, Acc_lpf_1st, Acc_lpf_2nd; 
	

	

};
void IMU_Init();
	
	//更新传感器数据
void IMU_UpdateSensor();	
	
	//计算飞行器姿态
void IMU_GetAttitude();
extern IMU imu;

#endif


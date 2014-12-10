#ifndef __IMU_H
#define __IMU_H

#include "config.h"

struct IMU 
{

	//ŷ���Ǳ�ʾ�ķ�������̬
	vector3f_t angle;
	
	vector3f_t Gyro, Acc, Acc_lpf_1st, Acc_lpf_2nd; 
	
};
void IMU_Init(void);
	
	//���´���������
void IMU_UpdateSensor(void);	
	
	//�����������̬
void IMU_GetAttitude(void);
extern struct IMU  imu;

#endif


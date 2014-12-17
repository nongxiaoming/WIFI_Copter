#ifndef __IMU_H
#define __IMU_H

#include "config.h"

struct IMU
{

	//ŷ���Ǳ�ʾ�ķ�������̬
	Vector3f angle;
	
	Vector3f Gyro, Acc, Acc_lpf; 

	LPF2ndData_t Acc_lpf_2nd;

	float magHold;

};

void IMU_Init(void);
	
	//���´���������
void IMU_UpdateSensor(void);	
	
	//�����������̬
void IMU_GetAttitude(void);

extern struct IMU imu;

#endif


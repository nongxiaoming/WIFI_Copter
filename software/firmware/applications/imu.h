#ifndef __IMU_H
#define __IMU_H

#include "config.h"

struct IMU 
{

	//ŷ���Ǳ�ʾ�ķ�������̬
	Vector3f angle;
	
	Vector3f Gyro, Acc, Acc_lpf_1st, Acc_lpf_2nd; 
	

	

};
void IMU_Init();
	
	//���´���������
void IMU_UpdateSensor();	
	
	//�����������̬
void IMU_GetAttitude();
extern IMU imu;

#endif


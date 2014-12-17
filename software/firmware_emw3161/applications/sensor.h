#ifndef __SENSOR_H
#define __SENSOR_H

#include "params.h"
#include "ANO_Math.h"

#define CALIBRATING_GYRO_CYCLES             1000
#define CALIBRATING_ACC_CYCLES              400

#define MPU6050G_S250DPS            ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU6050G_S500DPS            ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU6050G_S2000DPS           ((float)0.0609756f)  // 0.0700000 dps/LSB
	
struct Sensor
{
	uint8_t Acc_CALIBRATED;
	uint8_t Gyro_CALIBRATED;
	Vector3i Acc_Offset,Gyro_Offset;
};

	//��ʼ��Sensor
	void Sensor_Init(void);
	//��ȡ���ٶ� ���ٶ�
	void Sensor_ReadData(void);
	//���ؼ��ٶȵ�ֵ
	Vector3f Sensor_GetAcc(void);
	//���ؽ��ٶȵ�ֵ
	Vector3f Sensor_GetGyro(void);
	//���ص�λΪ��ÿ��Ľ��ٶ�
	Vector3f Sensor_GetGyro_in_dps(void);
extern struct Sensor sensor;


#endif

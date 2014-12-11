#ifndef __DRV_MPU6050_H
#define	__DRV_MPU6050_H
#include "ANO_Math.h"
#include "board.h"


#define CALIBRATING_GYRO_CYCLES             1000
#define CALIBRATING_ACC_CYCLES              400

typedef struct
{
	u8 Acc_CALIBRATED;
	u8 Gyro_CALIBRATED;
	Vector3i Acc_Offset,Gyro_Offset;
}mpu6050_t;

extern mpu6050_t mpu6050;
	//��ʼ��6050
	void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//��ȡ���ٶ�
	void MPU6050_ReadAccData(void);
	//��ȡ���ٶ�
	void MPU6050_ReadGyroData(void);
	//���ؼ��ٶȵ�ֵ
	Vector3f MPU6050_GetAcc(void);
	//���ؽ��ٶȵ�ֵ
	Vector3f MPU6050_GetGyro(void);
	//���ص�λΪ��ÿ��Ľ��ٶ�
	Vector3f MPU6050_GetGyro_in_dps(void);


#endif









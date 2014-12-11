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
	//初始化6050
	void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//读取加速度
	void MPU6050_ReadAccData(void);
	//读取角速度
	void MPU6050_ReadGyroData(void);
	//返回加速度的值
	Vector3f MPU6050_GetAcc(void);
	//返回角速度的值
	Vector3f MPU6050_GetGyro(void);
	//返回单位为度每秒的角速度
	Vector3f MPU6050_GetGyro_in_dps(void);


#endif









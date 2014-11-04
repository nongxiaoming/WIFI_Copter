#ifndef __SENSOR_H
#define __SENSOR_H

#include <rtthread.h>

#include "ANO_Math.h"

#define CALIBRATING_GYRO_CYCLES             1000
#define CALIBRATING_ACC_CYCLES              400

class Sensor
{
public:
	
	Sensor(void);

	bool Acc_CALIBRATED;
	bool Gyro_CALIBRATED;
	Vector3i Acc_Offset,Gyro_Offset;

	//初始化6050
	void Init(uint16_t sample_rate, uint16_t lpf);
	//读取加速度
	void Read_Acc_Data(void);
	//读取角速度
	void Read_Gyro_Data(void);
	//返回加速度的值
	Vector3f Get_Acc(void);
	//返回角速度的值
	Vector3f Get_Gyro(void);
	//返回单位为度每秒的角速度
	Vector3f Get_Gyro_in_dps(void);

private:
	
	rt_uint8_t mpu6050_buffer[14]; //接收数据缓存区
	Vector3f Acc_ADC,Gyro_ADC;
	Vector3f Gyro_dps;

	//加速度零偏矫正
	void CalOffset_Acc(void);
	//陀螺仪零偏矫正
	void CalOffset_Gyro(void);

	void delayms(uint16_t ms);
};

extern Sensor sensor;


#endif

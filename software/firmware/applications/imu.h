#ifndef __IMU_H
#define __IMU_H

#include "ANO_Config.h"

class IMU : public Filter
{
	
public:

	IMU();
	
	//欧拉角表示的飞行器姿态
	Vector3f angle;
	
	Vector3f Gyro, Acc, Acc_lpf_1st, Acc_lpf_2nd; 
	
	void Init();
	
	//更新传感器数据
	void updateSensor();	
	
	//计算飞行器姿态
	void getAttitude();
	
private:
	
	Quaternion Q;

	//基于四元数和互补滤波的姿态解算
	void Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT);

	//滤波器参数初始化
	void filter_Init();
	//传感器初始化
	void sensor_Init();

};

extern IMU imu;

#endif


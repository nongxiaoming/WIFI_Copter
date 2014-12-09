/******************** (C) COPYRIGHT 2014 ANO Tech *******************************
 * 作者		 ：匿名科创
 * 文件名  ：imu.cpp
 * 描述    ：飞行器姿态计算
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "imu.h"
#include "sensor.h"

IMU imu;

IMU::IMU()
{
}

//IMU初始化
void IMU::Init()
{
	//加速度一阶低通滤波器系数计算
	ano.factor.acc_lpf = LowPassFilter_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	//互补滤波器系数计算
	ano.factor.gyro_cf = ComplementaryFilter_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);
	
	//初始化MPU6050，1Khz采样率，98Hz低通滤波
	Sensor_Init(1000,98);	
}

//更新传感器数据
void IMU::updateSensor()
{
	//读取加速度和角速度
	Sensor_ReadData();
	//获取角速度，单位为度每秒
	Gyro = Sensor_GetGyro_in_dps();
	//获取加速度采样值
	Acc = Sensor_GetAcc();
}


//计算飞行器姿态
void IMU::getAttitude()
{
	//加速度数据一阶低通滤波
	Acc_lpf_1st = LowPassFilter_1st(Acc_lpf_1st, Acc, ano.factor.acc_lpf);
	
	//四元数更新姿态
	Quaternion_CF(Gyro,Acc_lpf_1st,IMU_LOOP_TIME*1e-6);
}


#define Kp 2.0f        //加速度权重，越大则向加速度测量值收敛越快
#define Ki 0.001f      //误差积分增益
//四元数更新姿态
void IMU::Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	Vector3f V_gravity, V_error, V_error_I;
	
	//重力加速度归一化
	acc.normalize();
	
	//提取四元数的等效余弦矩阵中的重力分量
	Q.vector_gravity(V_gravity);
	
	//向量叉积得出姿态误差
	V_error = acc % V_gravity;
	
	//对误差进行积分	
	V_error_I += V_error * Ki;
	
	//互补滤波，姿态误差补偿到角速度上，修正角速度积分漂移
	Gyro += V_error * Kp + V_error_I;		
	
	//一阶龙格库塔法更新四元数
	Q.Runge_Kutta_1st(Gyro, deltaT);
	
	//四元数归一化
	Q.normalize();
	
	//四元数转欧拉角
	Q.to_euler(&angle.x, &angle.y, &angle.z);
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

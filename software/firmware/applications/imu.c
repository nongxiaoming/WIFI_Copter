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

struct IMU  imu;

static	Quaternion Q;

	//基于四元数和互补滤波的姿态解算
static	void Quaternion_CF(vector3f_t gyro,vector3f_t acc, float deltaT);

//IMU初始化
void IMU_Init()
{
	//加速度一阶低通滤波器系数计算
	config.acc_lpf = LowPassFilter_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	//互补滤波器系数计算
	config.gyro_cf = ComplementaryFilter_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);
	
	//初始化MPU6050，1Khz采样率，98Hz低通滤波
	Sensor_Init(1000,98);	
}

//更新传感器数据
void IMU_UpdateSensor()
{
	//读取加速度和角速度
	Sensor_ReadData();
	//获取角速度，单位为度每秒
	imu.Gyro = Sensor_GetGyro_in_dps();
	//获取加速度采样值
	imu.Acc = Sensor_GetAcc();
}


//计算飞行器姿态
void IMU_GetAttitude()
{
	//加速度数据一阶低通滤波
	imu.Acc_lpf_1st = LowPassFilter_1st(imu.Acc_lpf_1st, imu.Acc, config.acc_lpf);
	
	//四元数更新姿态
	Quaternion_CF(imu.Gyro,imu.Acc_lpf_1st,IMU_LOOP_TIME*1e-6);
}


#define Kp 2.0f        //加速度权重，越大则向加速度测量值收敛越快
#define Ki 0.001f      //误差积分增益
//四元数更新姿态
static void Quaternion_CF(vector3f_t gyro,vector3f_t acc, float deltaT)
{
	vector3f_t V_gravity, V_error, V_error_I;
	float len;
	//重力加速度归一化
	len = Vector3_length(acc);
	acc.x /= len;
	acc.y /= len;
	acc.z /= len;
	
	//提取四元数的等效余弦矩阵中的重力分量
	Quaternion_vector_gravity(Q,&V_gravity);
	
	//向量叉积得出姿态误差
	V_error.x = acc.y*V_gravity.z - acc.z*V_gravity.y;
	V_error.y = acc.z*V_gravity.x - acc.x*V_gravity.z;
	V_error.z = acc.x*V_gravity.y - acc.y*V_gravity.x;
	
	//对误差进行积分	
	V_error_I.x += V_error.x * Ki;
	V_error_I.y += V_error.y * Ki;
	V_error_I.z += V_error.z * Ki;
	
	//互补滤波，姿态误差补偿到角速度上，修正角速度积分漂移
	imu.Gyro.x += V_error.x * Kp + V_error_I.x;
	imu.Gyro.y += V_error.y * Kp + V_error_I.y;
	imu.Gyro.z += V_error.z * Kp + V_error_I.z;
	
	//一阶龙格库塔法更新四元数
	Quaternion_Runge_Kutta_1st(&Q,&imu.Gyro, deltaT);
	
	//四元数归一化
	Quaternion_normalize(&Q);
	
	//四元数转欧拉角
	Quaternion_toEuler(Q,&imu.angle.x, &imu.angle.y, &imu.angle.z);
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

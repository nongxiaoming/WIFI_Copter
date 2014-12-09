/******************** (C) COPYRIGHT 2014 ANO Tech *******************************
 * ����		 �������ƴ�
 * �ļ���  ��imu.cpp
 * ����    ����������̬����
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "imu.h"
#include "sensor.h"

IMU imu;

IMU::IMU()
{
}

//IMU��ʼ��
void IMU::Init()
{
	//���ٶ�һ�׵�ͨ�˲���ϵ������
	ano.factor.acc_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	//�����˲���ϵ������
	ano.factor.gyro_cf = CF_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);
	
	//��ʼ��MPU6050��1Khz�����ʣ�98Hz��ͨ�˲�
	Sensor_Init(1000,98);	
}

//���´���������
void IMU::updateSensor()
{
	//��ȡ���ٶȺͽ��ٶ�
	Sensor_ReadData();
	//��ȡ���ٶȣ���λΪ��ÿ��
	Gyro = Sensor_GetGyro_in_dps();
	//��ȡ���ٶȲ���ֵ
	Acc = Sensor_GetAcc();
}


//�����������̬
void IMU::getAttitude()
{
	//���ٶ�����һ�׵�ͨ�˲�
	Acc_lpf_1st = LPF_1st(Acc_lpf_1st, Acc, ano.factor.acc_lpf);
	
	//��Ԫ��������̬
	Quaternion_CF(Gyro,Acc_lpf_1st,IMU_LOOP_TIME*1e-6);
}


#define Kp 2.0f        //���ٶ�Ȩ�أ�Խ��������ٶȲ���ֵ����Խ��
#define Ki 0.001f      //����������
//��Ԫ��������̬
void IMU::Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT)
{
	Vector3f V_gravity, V_error, V_error_I;
	
	//�������ٶȹ�һ��
	acc.normalize();
	
	//��ȡ��Ԫ���ĵ�Ч���Ҿ����е���������
	Q.vector_gravity(V_gravity);
	
	//��������ó���̬���
	V_error = acc % V_gravity;
	
	//�������л���	
	V_error_I += V_error * Ki;
	
	//�����˲�����̬���������ٶ��ϣ��������ٶȻ���Ư��
	Gyro += V_error * Kp + V_error_I;		
	
	//һ�����������������Ԫ��
	Q.Runge_Kutta_1st(Gyro, deltaT);
	
	//��Ԫ����һ��
	Q.normalize();
	
	//��Ԫ��תŷ����
	Q.to_euler(&angle.x, &angle.y, &angle.z);
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

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

struct IMU  imu;

static	Quaternion Q;

	//������Ԫ���ͻ����˲�����̬����
static	void Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT);

//IMU��ʼ��
void IMU_Init()
{
	//���ٶ�һ�׵�ͨ�˲���ϵ������
	config.acc_lpf = LowPassFilter_1st_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT);
	//�����˲���ϵ������
	config.gyro_cf = ComplementaryFilter_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);
	
	//��ʼ��MPU6050��1Khz�����ʣ�98Hz��ͨ�˲�
	Sensor_Init(1000,98);	
}

//���´���������
void IMU_UpdateSensor()
{
	//��ȡ���ٶȺͽ��ٶ�
	Sensor_ReadData();
	//��ȡ���ٶȣ���λΪ��ÿ��
	imu.Gyro = Sensor_GetGyro_in_dps();
	//��ȡ���ٶȲ���ֵ
	imu.Acc = Sensor_GetAcc();
}


//�����������̬
void IMU_GetAttitude()
{
	//���ٶ�����һ�׵�ͨ�˲�
	imu.Acc_lpf_1st = LowPassFilter_1st(imu.Acc_lpf_1st, imu.Acc, config.acc_lpf);
	
	//��Ԫ��������̬
	Quaternion_CF(imu.Gyro,imu.Acc_lpf_1st,IMU_LOOP_TIME*1e-6);
}


#define Kp 2.0f        //���ٶ�Ȩ�أ�Խ��������ٶȲ���ֵ����Խ��
#define Ki 0.001f      //����������
//��Ԫ��������̬
static void Quaternion_CF(Vector3f gyro,Vector3f acc, float deltaT)
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
	imu.Gyro += V_error * Kp + V_error_I;		
	
	//һ�����������������Ԫ��
	Q.Runge_Kutta_1st(imu.Gyro, deltaT);
	
	//��Ԫ����һ��
	Q.normalize();
	
	//��Ԫ��תŷ����
	Q.to_euler(&imu.angle.x, &imu.angle.y, &imu.angle.z);
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

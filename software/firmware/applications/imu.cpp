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
static	void Quaternion_CF(vector3f_t gyro,vector3f_t acc, float deltaT);

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
static void Quaternion_CF(vector3f_t gyro,vector3f_t acc, float deltaT)
{
	vector3f_t V_gravity, V_error, V_error_I;
	float len;
	//�������ٶȹ�һ��
	len = Vector3_length(acc);
	acc.x /= len;
	acc.y /= len;
	acc.z /= len;
	
	//��ȡ��Ԫ���ĵ�Ч���Ҿ����е���������
	Quaternion_vector_gravity(Q,&V_gravity);
	
	//��������ó���̬���
	V_error.x = acc.y*V_gravity.z - acc.z*V_gravity.y;
	V_error.y = acc.z*V_gravity.x - acc.x*V_gravity.z;
	V_error.z = acc.x*V_gravity.y - acc.y*V_gravity.x;
	
	//�������л���	
	V_error_I.x += V_error.x * Ki;
	V_error_I.y += V_error.y * Ki;
	V_error_I.z += V_error.z * Ki;
	
	//�����˲�����̬���������ٶ��ϣ��������ٶȻ���Ư��
	imu.Gyro.x += V_error.x * Kp + V_error_I.x;
	imu.Gyro.y += V_error.y * Kp + V_error_I.y;
	imu.Gyro.z += V_error.z * Kp + V_error_I.z;
	
	//һ�����������������Ԫ��
	Quaternion_Runge_Kutta_1st(&Q,&imu.Gyro, deltaT);
	
	//��Ԫ����һ��
	Quaternion_normalize(&Q);
	
	//��Ԫ��תŷ����
	Quaternion_toEuler(Q,&imu.angle.x, &imu.angle.y, &imu.angle.z);
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

#ifndef __SENSOR_H
#define __SENSOR_H

#include <rtthread.h>
#include "params.h"
#include "ANO_Math.h"

#define CALIBRATING_GYRO_CYCLES             1000
#define CALIBRATING_ACC_CYCLES              400

class Sensor
{
public:
	
	Sensor(void);

	bool Acc_CALIBRATED;
	bool Gyro_CALIBRATED;
	vector3i_t Acc_Offset,Gyro_Offset;

	//��ʼ��6050
	void Init(uint16_t sample_rate, uint16_t lpf);
	//��ȡ���ٶ� ���ٶ�
	void ReadData(void);
	//���ؼ��ٶȵ�ֵ
	Vector3f Get_Acc(void);
	//���ؽ��ٶȵ�ֵ
	Vector3f Get_Gyro(void);
	//���ص�λΪ��ÿ��Ľ��ٶ�
	Vector3f Get_Gyro_in_dps(void);

private:
	
	rt_uint8_t mpu6050_buffer[14]; //�������ݻ�����
	Vector3f Acc_ADC,Gyro_ADC;
	Vector3f Gyro_dps;
  rt_device_t  mpu6050;
	//���ٶ���ƫ����
	void CalOffset_Acc(void);
	//��������ƫ����
	void CalOffset_Gyro(void);

	void delayms(uint16_t ms);
};

extern Sensor sensor;


#endif

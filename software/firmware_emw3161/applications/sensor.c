#include "params.h"
#include "sensor.h"
#include "drv_mpu6050.h"

struct Sensor  sensor;

static uint8_t mpu6050_buffer[14]; //�������ݻ�����
static Vector3f Acc_ADC,Gyro_ADC;
static Vector3f Gyro_dps;

	//���ٶ���ƫ����
static	void Sensor_CalOffsetAcc(void);
	//��������ƫ����
static	void Sensor_CalOffsetGyro(void);
//MPU6050��ʼ������������������ʣ���ͨ�˲�Ƶ��
void Sensor_Init(void)
{
	//uint8_t default_filter;
//  mpu6050 = rt_device_find("mpu6050");
//	if(mpu6050 == RT_NULL)
//	{
//	 rt_kprintf("can not find mpu6050 device!\n");
//	 return ;
//	}
//	rt_device_open(mpu6050,RT_DEVICE_FLAG_RDWR);
  //��ʼ��MPU6050��1Khz�����ʣ�42Hz��ͨ�˲�
	MPU6050_Init(1000,42);
}

//��ȡ���ٶȺͽ��ٶ�
void Sensor_ReadData(void)
{
	  //rt_device_read(mpu6050,MPU6050_RA_ACCEL_XOUT_H,mpu6050_buffer,sizeof(mpu6050_buffer));
    
	MPU6050_ReadData(mpu6050_buffer);
	
	  Acc_ADC.x = ((mpu6050_buffer[0] << 8) | mpu6050_buffer[1])- sensor.Acc_Offset.x;
    Acc_ADC.y = ((mpu6050_buffer[2] << 8) | mpu6050_buffer[3])- sensor.Acc_Offset.y;
    Acc_ADC.z = ((mpu6050_buffer[4] << 8) | mpu6050_buffer[5])- sensor.Acc_Offset.z;
    Gyro_ADC.x = ((mpu6050_buffer[8] << 8) | mpu6050_buffer[9])- sensor.Gyro_Offset.x;
    Gyro_ADC.y = ((mpu6050_buffer[10] << 8) | mpu6050_buffer[11])- sensor.Gyro_Offset.y;
    Gyro_ADC.z = ((mpu6050_buffer[12] << 8) | mpu6050_buffer[13])- sensor.Gyro_Offset.z;

	Sensor_CalOffsetGyro();
	Sensor_CalOffsetAcc();
}

Vector3f Sensor_GetAcc(void)
{
 return Acc_ADC;	
}

Vector3f Sensor_GetGyro(void)
{
 return Gyro_ADC;		
}

Vector3f Sensor_GetGyro_in_dps(void)
{
	Gyro_dps.x = radians(Gyro_ADC.x * MPU6050G_S2000DPS);   // dps
	Gyro_dps.y = radians(Gyro_ADC.y * MPU6050G_S2000DPS);   // dps
	Gyro_dps.z = radians(Gyro_ADC.z * MPU6050G_S2000DPS);   // dps	
	
	return Gyro_dps;
}

//���ٶ���ƫ����
static void Sensor_CalOffsetAcc(void)
{
	if(sensor.Acc_CALIBRATED)
		{
			static Vector3f	tempAcc;
			static uint16_t cnt_a=0;

			if(cnt_a==0)
			{
				sensor.Acc_Offset.x=0;
				sensor.Acc_Offset.y=0;
				sensor.Acc_Offset.z=0;
				cnt_a = 1;
				return;
			}			
			tempAcc.x += Acc_ADC.x;
			tempAcc.y += Acc_ADC.y;
			tempAcc.z += Acc_ADC.z;
			if(cnt_a == CALIBRATING_ACC_CYCLES)
			{
				sensor.Acc_Offset.x = tempAcc.x/cnt_a;
				sensor.Acc_Offset.y = tempAcc.y/cnt_a;
				sensor.Acc_Offset.z = tempAcc.z/cnt_a - ACC_1G;
				cnt_a = 0;
				sensor.Acc_CALIBRATED = 0;
				Params_setAccOffset(sensor.Acc_Offset);
				Params_Save();//��������
				return;
			}
			cnt_a++;		
		}	
	
}

//��������ƫ����
static void Sensor_CalOffsetGyro(void)
{
	if(sensor.Gyro_CALIBRATED)
	{
		static Vector3f	tempGyro;
		static uint16_t cnt_g=0;
		if(cnt_g==0)
		{
			sensor.Gyro_Offset.x=0;
			sensor.Gyro_Offset.y=0;
			sensor.Gyro_Offset.z=0;
			tempGyro.x = tempGyro.y = tempGyro.z =0;
			cnt_g = 1;
			return;
		}
		tempGyro.x += Gyro_ADC.x;
		tempGyro.y += Gyro_ADC.y;
		tempGyro.z += Gyro_ADC.z;
		if(cnt_g == CALIBRATING_GYRO_CYCLES)
		{
			sensor.Gyro_Offset.x = tempGyro.x/cnt_g;
			sensor.Gyro_Offset.y = tempGyro.y/cnt_g;
			sensor.Gyro_Offset.z = tempGyro.z/cnt_g;
			cnt_g = 0;
			sensor.Gyro_CALIBRATED = 0;
			Params_setGyroOffset(sensor.Gyro_Offset);
			Params_Save();//��������
			return;
		}
		cnt_g++;
	}
}

#include "params.h"
#include "sensor.h"
#include "mpu6050.h"

Sensor sensor;

Sensor::Sensor()
{
	
}

//MPU6050初始化，传入参数：采样率，低通滤波频率
void Sensor::Init(uint16_t sample_rate, uint16_t lpf)
{
	//uint8_t default_filter;
  this->mpu6050 = rt_device_find("mpu6050");
	if(this->mpu6050 == RT_NULL)
	{
	 rt_kprintf("can not find mpu6050 device!\n");
	 return ;
	}
	rt_device_open(this->mpu6050,RT_DEVICE_FLAG_RDWR);
//	rt_device_control(this->mpu6050,1,&sample_rate);
//	rt_device_control(this->mpu6050,1,&lpf);
}

//读取加速度和角速度
void Sensor::ReadData(void)
{
	  rt_device_read(this->mpu6050,MPU6050_RA_ACCEL_XOUT_H,this->mpu6050_buffer,sizeof(this->mpu6050_buffer));
    
	  Acc_ADC.x = ((mpu6050_buffer[0] << 8) | mpu6050_buffer[1])- Acc_Offset.x;
    Acc_ADC.y = ((mpu6050_buffer[2] << 8) | mpu6050_buffer[3])- Acc_Offset.y;
    Acc_ADC.z = ((mpu6050_buffer[4] << 8) | mpu6050_buffer[5])- Acc_Offset.z;
    Gyro_ADC.x = ((mpu6050_buffer[8] << 8) | mpu6050_buffer[9])-Gyro_Offset.x;
    Gyro_ADC.y = ((mpu6050_buffer[10] << 8) | mpu6050_buffer[11])-Gyro_Offset.y;
    Gyro_ADC.z = ((mpu6050_buffer[12] << 8) | mpu6050_buffer[13])-Gyro_Offset.z;

	CalOffset_Gyro();
	CalOffset_Acc();
}

Vector3f Sensor::Get_Acc(void)
{
 return Acc_ADC;	
}

Vector3f Sensor::Get_Gyro(void)
{
 return Gyro_ADC;		
}

Vector3f Sensor::Get_Gyro_in_dps(void)
{
	Gyro_dps.x = radians(Gyro_ADC.x * MPU6050G_S2000DPS);   // dps
	Gyro_dps.y = radians(Gyro_ADC.y * MPU6050G_S2000DPS);   // dps
	Gyro_dps.z = radians(Gyro_ADC.z * MPU6050G_S2000DPS);   // dps	
	
	return Gyro_dps;
}

//加速度零偏矫正
void Sensor::CalOffset_Acc(void)
{
	if(Acc_CALIBRATED)
		{
			static Vector3f	tempAcc;
			static uint16_t cnt_a=0;

			if(cnt_a==0)
			{
				Acc_Offset.x=0;
				Acc_Offset.y=0;
				Acc_Offset.z=0;
				cnt_a = 1;
				return;
			}			
			tempAcc += Acc_ADC;
			if(cnt_a == CALIBRATING_ACC_CYCLES)
			{
				Acc_Offset.x = tempAcc.x/cnt_a;
				Acc_Offset.y = tempAcc.y/cnt_a;
				Acc_Offset.z = tempAcc.z/cnt_a - ACC_1G;
				cnt_a = 0;
				Acc_CALIBRATED = 0;
				params.set_acc_offset(Acc_Offset);
				params.Save();//保存数据
				return;
			}
			cnt_a++;		
		}	
	
}

//陀螺仪零偏矫正
void Sensor::CalOffset_Gyro(void)
{
	if(Gyro_CALIBRATED)
	{
		static Vector3f	tempGyro;
		static uint16_t cnt_g=0;
		if(cnt_g==0)
		{
			Gyro_Offset.x=0;
			Gyro_Offset.y=0;
			Gyro_Offset.z=0;
			tempGyro(0, 0, 0);
			cnt_g = 1;
			return;
		}
		tempGyro += Gyro_ADC;
		if(cnt_g == CALIBRATING_GYRO_CYCLES)
		{
			Gyro_Offset.x = tempGyro.x/cnt_g;
			Gyro_Offset.y = tempGyro.y/cnt_g;
			Gyro_Offset.z = tempGyro.z/cnt_g;
			cnt_g = 0;
			Gyro_CALIBRATED = 0;
			params.set_gyro_offset(Gyro_Offset);
			params.Save();//保存数据
			return;
		}
		cnt_g++;
	}
}


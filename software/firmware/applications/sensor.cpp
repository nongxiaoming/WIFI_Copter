#include "sensor.h"
#include "params.h"

Sensor sensor;

Sensor::Sensor()
{
	
}

//MPU6050��ʼ������������������ʣ���ͨ�˲�Ƶ��
void Sensor::Init(uint16_t sample_rate, uint16_t lpf)
{
	uint8_t default_filter;

}

//��ȡ���ٶ�
void Sensor::Read_Acc_Data(void)
{
	int16_t acc_temp[3];
	
//	mpu6050_buffer[0] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_L); 
//	mpu6050_buffer[1] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_H);
//	acc_temp[0] = ((((int16_t)mpu6050_buffer[1]) << 8) | mpu6050_buffer[0])- Acc_Offset.x;  //���ٶ�X��

//	mpu6050_buffer[2] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_L);
//	mpu6050_buffer[3] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_H);
//	acc_temp[1] = ((((int16_t)mpu6050_buffer[3]) << 8) | mpu6050_buffer[2])- Acc_Offset.y;  //���ٶ�Y��

//	mpu6050_buffer[4] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_L);
//	mpu6050_buffer[5] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_H);
//	acc_temp[2] = ((((int16_t)mpu6050_buffer[5]) << 8) | mpu6050_buffer[4])- Acc_Offset.z;  //���ٶ�Z��
	
	Acc_ADC((float)acc_temp[0],(float)acc_temp[1],(float)acc_temp[2]);
	
	CalOffset_Acc();
}

//��ȡ���ٶ�
void Sensor::Read_Gyro_Data(void)
{
	int16_t gyro_temp[3];
	
//	mpu6050_buffer[6] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_L); 
//	mpu6050_buffer[7] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_H);
//	gyro_temp[0] = ((((int16_t)mpu6050_buffer[7]) << 8) | mpu6050_buffer[6])- Gyro_Offset.x;	//������X��

//	mpu6050_buffer[8] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_L);
//	mpu6050_buffer[9] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_H);
//	gyro_temp[1] = ((((int16_t)mpu6050_buffer[9]) << 8) | mpu6050_buffer[8])- Gyro_Offset.y;	//������Y��

//	mpu6050_buffer[10] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_L);
//	mpu6050_buffer[11] = I2C_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_H);
//	gyro_temp[2] = ((((int16_t)mpu6050_buffer[11]) << 8) | mpu6050_buffer[10])- Gyro_Offset.z;	  //������Z��		
	
	Gyro_ADC((float)gyro_temp[0], (float)gyro_temp[1], (float)gyro_temp[2]);
	
	CalOffset_Gyro();
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
//	Gyro_dps.x = radians(Gyro_ADC.x * MPU6050G_s2000dps);   // dps
//	Gyro_dps.y = radians(Gyro_ADC.y * MPU6050G_s2000dps);   // dps
//	Gyro_dps.z = radians(Gyro_ADC.z * MPU6050G_s2000dps);   // dps	
	return Gyro_dps;
}

//���ٶ���ƫ����
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
				params.SAVE_ACC_OFFSET();//��������
				return;
			}
			cnt_a++;		
		}	
	
}

//��������ƫ����
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
			params.SAVE_GYRO_OFFSET();//��������
			return;
		}
		cnt_g++;
	}
}


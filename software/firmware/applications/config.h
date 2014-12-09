#ifndef __CONFIG_H
#define __CONFIG_H

#include "board.h"
#include "filter.h"
#include "imu.h"
#include "ANO_DT.h"
#include "ANO_RC.h"


/*----------------------IMU--------------------*/
#define ANO_IMU_USE_DCM_CF

#define IMU_LOOP_TIME		2000	//��λΪuS
#define PID_LOOP_TIME		2000	//��λΪus

#define ACC_1G 			4096		//�ɼ��ٶȼƵ�����ȷ��
#define ACC_LPF_CUT 10.0f		//���ٶȵ�ͨ�˲�����ֹƵ��10Hz

#define GYRO_CF_TAU 1.2f
/*---------------------------------------------*/

/*-------------------�������ݷ��ͷ�ʽѡ��-----------------*/
//#define ANO_DT_USE_Bluetooth
//#define ANO_DT_USE_NRF24l01
#define ANO_DT_USE_WIFI
/*--------------------------------------------------------*/


struct Config
{	
			float acc_lpf;		
			float gyro_cf;		

			uint8_t ARMED;
			uint8_t failsafe;
	
};

extern struct Config config;

#endif

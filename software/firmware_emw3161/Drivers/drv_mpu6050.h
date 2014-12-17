#ifndef __DRV_MPU6050_H
#define	__DRV_MPU6050_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#include "board.h"


	//��ʼ��6050
void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//��ȡ���ٶȺͽ��ٶ�����
void MPU6050_ReadData(uint8_t *buffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif


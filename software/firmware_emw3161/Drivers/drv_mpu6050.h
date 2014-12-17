#ifndef __DRV_MPU6050_H
#define	__DRV_MPU6050_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#include "board.h"


	//初始化6050
void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//读取加速度和角速度数据
void MPU6050_ReadData(uint8_t *buffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif


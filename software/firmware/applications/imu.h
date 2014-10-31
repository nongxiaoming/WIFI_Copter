#ifndef _IMU_H_
#define _IMU_H_
#include "stm32f2xx.h"
//#include "MPU6050.h"
#include "sensor.h"

extern vs16 	Mx_Offset,My_Offset,Mz_Offset;
extern float 	My_Gain,Mz_Gain;
extern float 	AngleOffset_Rol,AngleOffset_Pit; 

void Prepare_Data(rt_axes3i_t *acc_in,rt_axes3i_t *acc_out);

void IMUupdate(rt_axes3i_t *gyr, rt_axes3i_t *acc, rt_angle3f_t *angle);

void Cal_Compass(void);
void Get_CompassAngle(rt_axes3i_t *mag, rt_axes3i_t *acc, float *heading);

#endif

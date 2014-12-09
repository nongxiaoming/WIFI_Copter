#ifndef _IMU_H_
#define _IMU_H_
#include "stm32f2xx.h"
#include "MPU6050.h"
#include "sysconfig.h"

extern vs16 	Mx_Offset,My_Offset,Mz_Offset;
extern float 	My_Gain,Mz_Gain;
extern float 	AngleOffset_Rol,AngleOffset_Pit; 

void Prepare_Data(T_int16_xyz *acc_in,T_int16_xyz *acc_out);

void IMUupdate(T_int16_xyz *gyr, T_int16_xyz *acc, T_float_angle *angle);

void Cal_Compass(void);
void Get_CompassAngle(T_int16_xyz *mag, T_int16_xyz *acc, float *heading);

#endif

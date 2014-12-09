#ifndef __FILTER_H
#define __FILTER_H

#include "ANO_Math.h"



	//一阶低通滤波器系数计算
	float LowPassFilter_1st_Factor_Cal(float deltaT, float Fcut);
	
	//互补滤波器系数计算
	float ComplementaryFilter_Factor_Cal(float deltaT, float tau);
	
	//一阶低通滤波器
	vector3f_t LowPassFilter_1st(vector3f_t oldData, vector3f_t newData, float lpf_factor);

	//一阶互补滤波器
	vector3f_t ComplementaryFilter_1st(vector3f_t gyroData, vector3f_t accData, float cf_factor);
	
	
#endif


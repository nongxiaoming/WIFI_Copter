#ifndef __FILTER_H
#define __FILTER_H

#include "ANO_Math.h"



	//һ�׵�ͨ�˲���ϵ������
	float LowPassFilter_1st_Factor_Cal(float deltaT, float Fcut);
	
	//�����˲���ϵ������
	float ComplementaryFilter_Factor_Cal(float deltaT, float tau);
	
	//һ�׵�ͨ�˲���
	vector3f_t LowPassFilter_1st(vector3f_t oldData, vector3f_t newData, float lpf_factor);

	//һ�׻����˲���
	vector3f_t ComplementaryFilter_1st(vector3f_t gyroData, vector3f_t accData, float cf_factor);
	
	
#endif


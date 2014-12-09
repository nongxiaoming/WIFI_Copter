#ifndef __FILTER_H
#define __FILTER_H

#include "ANO_Math.h"



	//һ�׵�ͨ�˲���ϵ������
	float LowPassFilter_1st_Factor_Cal(float deltaT, float Fcut);
	
	//�����˲���ϵ������
	float ComplementaryFilter_Factor_Cal(float deltaT, float tau);
	
	//һ�׵�ͨ�˲���
	Vector3f LowPassFilter_1st(Vector3f oldData, Vector3f newData, float lpf_factor);

	//һ�׻����˲���
	Vector3f ComplementaryFilter_1st(Vector3f gyroData, Vector3f accData, float cf_factor);
	
	
#endif


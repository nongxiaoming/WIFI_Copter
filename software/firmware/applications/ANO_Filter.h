#ifndef __ANO_FILTER_H
#define __ANO_FILTER_H

#include "ANO_Math.h"

class ANO_Filter
{
	
public:

	ANO_Filter(){
	}

	//һ�׵�ͨ�˲���ϵ������
	float LPF_1st_Factor_Cal(float deltaT, float Fcut);
	
	//�����˲���ϵ������
	float CF_Factor_Cal(float deltaT, float tau);
	
	//һ�׵�ͨ�˲���
	Vector3f LPF_1st(Vector3f oldData, Vector3f newData, float lpf_factor);

	//һ�׻����˲���
	Vector3f CF_1st(Vector3f gyroData, Vector3f accData, float cf_factor);
	
};


#endif


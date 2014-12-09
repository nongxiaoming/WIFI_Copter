/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Filter.cpp
 * 描述    ：滤波器相关函数
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "filter.h"


/*----------------------低通滤波器系数计算-------------------------*/
float LowPassFilter_1st_Factor_Cal(float deltaT, float Fcut)
{
	return deltaT / (deltaT + 1 / (2 * M_PI * Fcut));
}

/*----------------------一阶低通滤波器------------------------*/
vector3f_t LowPassFilter_1st(vector3f_t oldData, vector3f_t newData, float lpf_factor)
{ 
	vector3f_t temp;
	temp.x = oldData.x * (1 - lpf_factor) + newData.x * lpf_factor;
	temp.y = oldData.y * (1 - lpf_factor) + newData.y * lpf_factor;
	temp.z = oldData.z * (1 - lpf_factor) + newData.z * lpf_factor;
	return temp;
}

/*----------------------互补滤波器系数计算-------------------------*/
float ComplementaryFilter_Factor_Cal(float deltaT, float tau)
{
	return tau / (deltaT + tau);
}

/*----------------------一阶互补滤波器-----------------------------*/
vector3f_t ComplementaryFilter_1st(vector3f_t gyroData, vector3f_t accData, float cf_factor)
{ 
	vector3f_t temp;
	temp.x=gyroData.x * cf_factor +accData.x *(1 - cf_factor);
	temp.y=gyroData.x * cf_factor +accData.y *(1 - cf_factor);
	temp.z=gyroData.x * cf_factor +accData.z *(1 - cf_factor);
	return temp;	
}





/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

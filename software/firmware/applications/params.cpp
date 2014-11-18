/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "params.h"
#include "sensor.h"
#include "board.h"

Params params;


void Params::Init(void)
{

   this->value = (params_t*)rt_malloc(sizeof(params_t));
	 if(this->Read()==RT_EOK)
   {
	  
	 }else
   {
	   this->Save();
	 }
	
}

void Params::set_acc_offset(vector3i_t offset)
{
 this->value->acc_offset = offset;
}
vector3i_t Params::get_acc_offset(void)
{
  return this->value->acc_offset;
}

void Params::set_gyro_offset(vector3i_t offset)
{
 this->value->gyro_offset = offset;
}
vector3i_t Params::get_gyro_offset(void)
{
 return this->value->gyro_offset;
}

void Params::set_roll_pid(pid_t val)
{
this->value->roll_pid = val;
}
pid_t Params::get_roll_pid(void)
{
 return this->value->roll_pid;
}

void Params::set_pitch_pid(pid_t val)
{
this->value->pitch_pid = val;
}
pid_t Params::get_pitch_pid(void)
{
 return this->value->pitch_pid;
}

void Params::set_yaw_pid(pid_t val)
{
this->value->yaw_pid = val;
}
pid_t Params::get_yaw_pid(void)
{
 return this->value->yaw_pid;
}

rt_err_t Params::Read(void)
{

	return RT_EOK;
}
void Params::Save(void)
{

}










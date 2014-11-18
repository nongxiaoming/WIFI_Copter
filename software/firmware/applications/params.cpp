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

//	if(READ_FirstInitFlag()!= FirstInitFlag)	//板子从未初始化
//	{
//		SAVE_PID();
//	}
//	
//	READ_CONF();
//	SAVE_FirstInitFlag();
	
}

void Params::SAVE_FirstInitFlag(void)
{
//	EE_WriteVariable(VirtAddVarTab[EE_FirstInitFlag], FirstInitFlag);
}

uint16_t Params::READ_FirstInitFlag(void)
{
//	uint16_t temp;
//	EE_ReadVariable(VirtAddVarTab[EE_FirstInitFlag], &temp);
	return 0;//temp;
}

void Params::SAVE_ACC_OFFSET(void)
{
//	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_X_OFFSET_ADDR], sensor.Acc_Offset.x);
//	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_Y_OFFSET_ADDR], sensor.Acc_Offset.y);
//	EE_WriteVariable(VirtAddVarTab[EE_6050_ACC_Z_OFFSET_ADDR], sensor.Acc_Offset.z);
}
void Params::READ_ACC_OFFSET(void)
{
//	uint16_t temp[3];
//	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_X_OFFSET_ADDR], &temp[0]);
//	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_Y_OFFSET_ADDR], &temp[1]);
//	EE_ReadVariable(VirtAddVarTab[EE_6050_ACC_Z_OFFSET_ADDR], &temp[2]);
//	sensor.Acc_Offset.x = temp[0];
//	sensor.Acc_Offset.y = temp[1];
//	sensor.Acc_Offset.z = temp[2];
}
void Params::SAVE_GYRO_OFFSET(void)
{
//	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_X_OFFSET_ADDR], sensor.Gyro_Offset.x);
//	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_Y_OFFSET_ADDR], sensor.Gyro_Offset.y);
//	EE_WriteVariable(VirtAddVarTab[EE_6050_GYRO_Z_OFFSET_ADDR], sensor.Gyro_Offset.z);
}
void Params::READ_GYRO_OFFSET(void)
{
//	uint16_t temp[3];
//	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_X_OFFSET_ADDR], &temp[0]);
//	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_Y_OFFSET_ADDR], &temp[1]);
//	EE_ReadVariable(VirtAddVarTab[EE_6050_GYRO_Z_OFFSET_ADDR], &temp[2]);
//	sensor.Gyro_Offset.x = temp[0];
//	sensor.Gyro_Offset.y = temp[1];
//	sensor.Gyro_Offset.z = temp[2];
}
void Params::SAVE_PID(void)
{
//	u16 _temp;
//	_temp = pidctrl.pid[PIDROLL].kP;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_P],_temp);
//	_temp = pidctrl.pid[PIDROLL].kI;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_I],_temp);
//	_temp = pidctrl.pid[PIDROLL].kD;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_ROL_D],_temp);
//	_temp = pidctrl.pid[PIDPITCH].kP;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_P],_temp);
//	_temp = pidctrl.pid[PIDPITCH].kI;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_I],_temp);
//	_temp = pidctrl.pid[PIDPITCH].kD;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_PIT_D],_temp);
//	_temp = pidctrl.pid[PIDYAW].kP;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_P],_temp);
//	_temp = pidctrl.pid[PIDYAW].kI;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_I],_temp);
//	_temp = pidctrl.pid[PIDYAW].kD;
//	EE_WriteVariable(VirtAddVarTab[EE_PID_YAW_D],_temp);

}

void Params::READ_PID(void)
{
//	u16 _temp;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_P],&_temp);
//	pidctrl.pid[PIDROLL].kP = _temp;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_I],&_temp);
//	pidctrl.pid[PIDROLL].kI = _temp ;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_ROL_D],&_temp);
//	pidctrl.pid[PIDROLL].kD = _temp ;
//	
//	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_P],&_temp);
//	pidctrl.pid[PIDPITCH].kP = _temp ;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_I],&_temp);
//	pidctrl.pid[PIDPITCH].kI = _temp ;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_PIT_D],&_temp);
//	pidctrl.pid[PIDPITCH].kD = _temp ;
//	
//	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_P],&_temp);
//	pidctrl.pid[PIDYAW].kP = _temp ;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_I],&_temp);
//	pidctrl.pid[PIDYAW].kI = _temp ;
//	EE_ReadVariable(VirtAddVarTab[EE_PID_YAW_D],&_temp);
//	pidctrl.pid[PIDYAW].kD = _temp ;
}

void Params::READ_CONF(void)
{
	READ_PID();
	READ_ACC_OFFSET();
	READ_GYRO_OFFSET();
}











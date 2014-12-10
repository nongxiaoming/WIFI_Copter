#ifndef __PARAMS_H
#define __PARAMS_H

#include <rtthread.h>
#include "config.h"



typedef struct
{
	uint16_t kp;
	uint16_t ki;
	uint16_t kd;
}pid_t;

typedef struct
{
 uint32_t magic;
 vector3i_t acc_offset;
 vector3i_t gyro_offset;
 pid_t roll_pid;
 pid_t pitch_pid;
 pid_t yaw_pid;
}params_t;

#define MAGIC 0x12345678


void Params_Init(void);
	void Params_setAccOffset(vector3i_t offset);
  vector3i_t Params_getAccOffset(void);
  void Params_setGyroOffset(vector3i_t offset);
  vector3i_t Params_getGyroOffset(void);
	void Params_setRollPid(pid_t val);
  pid_t Params_getRollPid(void);
  void Params_setPitchPid(pid_t val);
  pid_t Params_getPitchPid(void);
  void Params_setYawPid(pid_t val);
  pid_t Params_getYawPid(void);
  void Params_Save(void);


#endif


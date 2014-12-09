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

class Params
{
	
public:
	
	void Init(void);
	void set_acc_offset(vector3i_t offset);
  vector3i_t get_acc_offset(void);
  void set_gyro_offset(vector3i_t offset);
  vector3i_t get_gyro_offset(void);
	void set_roll_pid(pid_t val);
  pid_t get_roll_pid(void);
  void set_pitch_pid(pid_t val);
  pid_t get_pitch_pid(void);
  void set_yaw_pid(pid_t val);
  pid_t get_yaw_pid(void);
  void Save(void);
private:
	 params_t *value;
	 rt_err_t Read(void);
};

extern Params params;

#endif


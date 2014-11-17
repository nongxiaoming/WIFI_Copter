#ifndef __PARAMS_H
#define __PARAMS_H

#include "ANO_Config.h"

typedef struct 
{
 int16_t x;
 int16_t y;
 int16_t z;
}vector3i_t;

typedef struct
{
 uint32_t magic;
 vector3i_t acc_offset;
 vector3i_t gyro_offset;
}params_t;

class Params
{
	
public:
	
	void Init(void);

	void SAVE_ACC_OFFSET(void);
	void SAVE_GYRO_OFFSET(void);
	void SAVE_PID(void);

private:
	
	void SAVE_FirstInitFlag(void);
	uint16_t READ_FirstInitFlag(void);
	void READ_ACC_OFFSET(void);
	void READ_GYRO_OFFSET(void);
	void READ_PID(void);
	void READ_CONF(void);
};

extern Params params;

#endif


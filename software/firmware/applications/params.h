#ifndef __PARAMS_H
#define __PARAMS_H

#include "ANO_Config.h"


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


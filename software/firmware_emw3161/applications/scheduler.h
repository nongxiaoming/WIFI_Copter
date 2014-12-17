#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "board.h"


struct Scheduler
{
	uint16_t cnt_1ms;
	uint16_t cnt_2ms;
	uint16_t cnt_5ms;
	uint16_t cnt_10ms;
	uint16_t cnt_20ms;
};

void Scheduler_Run(void);

void Scheduler_Init(void);

extern struct Scheduler scheduler;

#endif












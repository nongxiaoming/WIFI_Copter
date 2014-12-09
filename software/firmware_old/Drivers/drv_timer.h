#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H

#include "rtthread.h"
#include "stm32f2xx.h"

#define SYS_TIMx					TIM14
#define SYS_RCC_TIMx			RCC_APB1Periph_TIM14

void timer_hw_init(rt_uint32_t period);
#define timer_hw_start() TIM_Cmd(SYS_TIMx,ENABLE)
#define timer_hw_stop() TIM_Cmd(SYS_TIMx,ENABLE)

#endif

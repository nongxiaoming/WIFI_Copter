#include "drv_timer.h"


void timer_hw_init(rt_uint32_t period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//�������ã�ʱ���ͱȽ�������ã���������ֻ�趨ʱ�����Բ���OC�Ƚ����
	RCC_APB1PeriphClockCmd(SYS_RCC_TIMx,ENABLE);
	
	TIM_DeInit(SYS_TIMx);

	TIM_TimeBaseStructure.TIM_Period=period;//װ��ֵ

	TIM_TimeBaseStructure.TIM_Prescaler=60-1;//��Ƶϵ��

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(SYS_TIMx,&TIM_TimeBaseStructure);

	TIM_ClearFlag(SYS_TIMx,TIM_FLAG_Update);

	TIM_ITConfig(SYS_TIMx,TIM_IT_Update,ENABLE);

}


#include "timer_hw.h"

#define SYS_TIMx					TIM14
#define SYS_RCC_TIMx			RCC_APB1Periph_TIM14

void Timer_Sys_Init(u32 period_num)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//�������ã�ʱ���ͱȽ�������ã���������ֻ�趨ʱ�����Բ���OC�Ƚ����
	RCC_APB1PeriphClockCmd(SYS_RCC_TIMx,ENABLE);
	
	TIM_DeInit(SYS_TIMx);

	TIM_TimeBaseStructure.TIM_Period=period_num;//װ��ֵ

	TIM_TimeBaseStructure.TIM_Prescaler=60-1;//��Ƶϵ��

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(SYS_TIMx,&TIM_TimeBaseStructure);

	TIM_ClearFlag(SYS_TIMx,TIM_FLAG_Update);

	TIM_ITConfig(SYS_TIMx,TIM_IT_Update,ENABLE);


	NVIC_InitTypeDef NVIC_InitStructure;
	//Sys_Timer
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	TIM_Cmd(SYS_TIMx,ENABLE);
}
void Timer_Sys_Run(u8 ena)
{
	if(ena)
		TIM_Cmd(SYS_TIMx,ENABLE);
	else
		TIM_Cmd(SYS_TIMx,DISABLE);
}

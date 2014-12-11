/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：board.c
 * 描述    ：硬件初始化
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "board.h"
#include "ANO_Scheduler.h"

// cycles per microsecond
static volatile uint32_t usTicks = 0;
// 滴答定时器计数变量 ,49天后溢出
static volatile uint32_t sysTickUptime = 0;

static void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

void SysTick_IRQ(void)
{
	sysTickUptime++;
	scheduler.cnt_1ms++;
	scheduler.cnt_2ms++;
	scheduler.cnt_5ms++;
	scheduler.cnt_10ms++;
	scheduler.cnt_20ms++;
}

uint32_t GetSysTime_us(void) 
{
    register uint32_t ms, cycle_cnt;
    do {
        ms = sysTickUptime;
        cycle_cnt = SysTick->VAL;
    } while (ms != sysTickUptime);
    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void  board_Init(void)
{
	//初始化wifi库
	wifi_lib_init();
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//初始化系统滴答定时器
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	
	
	//初始化模拟I2C
	I2C_Soft_Init();
	
	//初始化wifi
	wifi_init();
 
	//初始化定时器输出PWM
	Motors_Init();
	
#ifdef ANO_DT_USE_UART	//使能UART通信
	//初始化Uart1
	Uart1_Init(115200);
#endif

  stationModeStart();
	LED_Init();
	LED_ON();	
	
	//解锁flash
	FLASH_Unlock();	

	
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��board.c
 * ����    ��Ӳ����ʼ��
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "board.h"
#include "ANO_Scheduler.h"

// cycles per microsecond
static volatile uint32_t usTicks = 0;
// �δ�ʱ���������� ,49������
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
	//��ʼ��wifi��
	wifi_lib_init();
	//�ж����ȼ��������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//��ʼ��ϵͳ�δ�ʱ��
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	
	
	//��ʼ��ģ��I2C
	I2C_Soft_Init();
	
	//��ʼ��wifi
	wifi_init();
 
	//��ʼ����ʱ�����PWM
	Motors_Init();
	
#ifdef ANO_DT_USE_UART	//ʹ��UARTͨ��
	//��ʼ��Uart1
	Uart1_Init(115200);
#endif

  stationModeStart();
	LED_Init();
	LED_ON();	
	
	//����flash
	FLASH_Unlock();	

	
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

#include <rtthread.h>
#include "board.h"


#define MOTORS_NUM_MAX    4


static rt_err_t rt_motors_init(rt_device_t dev)
{

	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	uint16_t PrescalerValue = 0;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
	
	/* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 20000000) - 1;
	/* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 2000;									//��װֵ
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						//��Ƶϵ��
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
	
    return RT_EOK;
}

static rt_err_t rt_motors_open(rt_device_t dev, rt_uint16_t oflag)
{	
    return RT_EOK;
}

static rt_err_t rt_motors_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_motors_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
    rt_uint8_t *value = buffer;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT((pos + size) <= MOTORS_NUM_MAX);

    for (index = 0; index < nr; index++)
    {

        value++;
    }
    return index;
}

static rt_size_t rt_motors_write(rt_device_t dev, rt_off_t pos,
                              const void *buffer, rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nw = size;
    const rt_uint8_t *value = buffer;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT((pos + size) <= MOTORS_NUM_MAX);

    for (index = 0; index < nw; index++)
    {
        if (*value++)
        {
            
        }
        else
        {
            
        }
    }
    return index;
}

static rt_err_t rt_motors_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{

    return RT_EOK;
}

void rt_led_hw_init(void)
{
	 rt_device_t device = RT_NULL;
	 device = rt_malloc(sizeof(struct rt_device));
	 if(device == RT_NULL)
    {
		 rt_kprintf("no mem to malloc motors device!\n");
			return ;
		}
    device->type         = RT_Device_Class_Char;
    device->rx_indicate  = RT_NULL;
    device->tx_complete  = RT_NULL;
    device->init         = rt_motors_init;
    device->open         = rt_motors_open;
    device->close        = rt_motors_close;
    device->read         = rt_motors_read;
    device->write        = rt_motors_write;
    device->control      = rt_motors_control;
    device->user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(device, "motors", RT_DEVICE_FLAG_RDWR);
  
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void motors_test(rt_uint32_t motors_num, rt_uint32_t value)
{
    rt_device_t dev = RT_NULL;
	  dev = rt_device_find("motors");
	 if(dev == RT_NULL)
   {
	  rt_kprintf("can not found motors device!\n");
		 return ;
	 }
	 rt_device_open(dev,RT_DEVICE_FLAG_RDWR);
	 
    rt_motors_write(dev, motors_num, &value, 1);
}
FINSH_FUNCTION_EXPORT(motors_test, e.g: motors_test(0, 100).)
#endif

#include <rtthread.h>
#include "board.h"

//#include "spi_wifi_rw009.h"

/*
SPI RS = P16
WIFI_IRQ_BUSY: PA2
*/

#define WIFI_RESET_PORT         GPIOA
#define WIFI_RESET_PIN          GPIO_Pin_3
#define WIFI_IRQ_BUSY_PORT      GPIOA
#define WIFI_IRQ_BUSY_PIN       GPIO_Pin_2
#define WIFI_IRQ_LINE           EXTI_Line2

rt_bool_t spi_wifi_is_busy(void)
{
    if (GPIO_ReadInputDataBit(WIFI_IRQ_BUSY_PORT, WIFI_IRQ_BUSY_PIN))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

void spi_wifi_int_cmd(int cmd)
{
    EXTI_InitTypeDef   EXTI_InitStructure;

    if (cmd)
    {
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_ClearITPendingBit(WIFI_IRQ_LINE);
    }
    else
    {
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    }

    EXTI_InitStructure.EXTI_Line = WIFI_IRQ_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&EXTI_InitStructure);
}

void spi_wifi_reset(rt_bool_t rst)
{
    if(rst)
        GPIO_ResetBits(WIFI_RESET_PORT, WIFI_RESET_PIN);
    else
        GPIO_SetBits(WIFI_RESET_PORT, WIFI_RESET_PIN);
}

void spi_wifi_hw_init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* RESET */
    {
        /* Configure GPIO pin as input floating */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

        GPIO_InitStructure.GPIO_Pin = WIFI_RESET_PIN;
        GPIO_Init(WIFI_RESET_PORT, &GPIO_InitStructure);

        spi_wifi_reset(RT_TRUE);
        rt_thread_delay(RT_TICK_PER_SECOND/10);
        spi_wifi_reset(RT_FALSE);
        rt_thread_delay(RT_TICK_PER_SECOND/10);
    }

    /* Configure GPIO pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_InitStructure.GPIO_Pin = WIFI_IRQ_BUSY_PIN;
    GPIO_Init(WIFI_IRQ_BUSY_PORT, &GPIO_InitStructure);

    /* Connect EXTI Line to GPIO */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

    /* Enable and set EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

extern void spi_wifi_isr(int vector);
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(WIFI_IRQ_LINE) != RESET)
    {
        spi_wifi_isr(0);

        /* Clear the EXTI line pending bit */
        EXTI_ClearITPendingBit(WIFI_IRQ_LINE);
    }
}

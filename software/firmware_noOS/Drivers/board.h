
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f2xx.h"
#include "string.h"
#include "ANO_Math.h"

#define ARMAPI extern "C"

/***************LED GPIO定义******************/
#define ANO_RCC_LED			RCC_AHB1Periph_GPIOD
#define ANO_GPIO_LED		GPIOD
#define ANO_Pin_LED			GPIO_Pin_2
/*********************************************/
/***************I2C GPIO定义******************/
#define ANO_GPIO_I2C	GPIOB
#define I2C_Pin_SCL		GPIO_Pin_10
#define I2C_Pin_SDA		GPIO_Pin_11
#define ANO_RCC_I2C		RCC_AHB1Periph_GPIOB
/*********************************************/
/***************SPI2 GPIO定义******************/
#define ANO_GPIO_SPI2		GPIOB
#define ANO_GPIO_CE2		GPIOA
#define SPI2_Pin_SCK		GPIO_Pin_13
#define SPI2_Pin_MISO		GPIO_Pin_14
#define SPI2_Pin_MOSI		GPIO_Pin_15
#define SPI2_Pin_CE2		GPIO_Pin_8
#define SPI2_Pin_CSN		GPIO_Pin_12
#define RCC_GPIO_SPI2		RCC_APB2Periph_GPIOB
#define RCC_GPIO_CE2		RCC_APB2Periph_GPIOA
/*********************************************/

/***************硬件中断优先级******************/
#define NVIC_UART_P	5
#define NVIC_UART_S	1
#define NVIC_TIM4_P	2
#define NVIC_TIM4_S	1
/***********************************************/

#include "ANO_Config.h"
#include "ANO_Drv_LED.h"
#include "ANO_Drv_I2C_soft.h"
#include "ANO_Drv_MPU6050.h"
#include "ANO_Drv_Uart.h"

void ANO_Hexacopter_board_Init(void);
void SysTick_IRQ(void);
uint32_t GetSysTime_us(void);


#endif /* __BOARD_H__ */

// 





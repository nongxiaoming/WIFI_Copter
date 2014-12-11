
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f2xx.h"
#include "string.h"

#define ARMAPI extern "C"

/***************I2C GPIO����******************/
#define ANO_GPIO_I2C	GPIOB
#define I2C_Pin_SCL		GPIO_Pin_6
#define I2C_Pin_SDA		GPIO_Pin_7
#define ANO_RCC_I2C		RCC_AHB1Periph_GPIOB
/*********************************************/
/***************SPI2 GPIO����******************/
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

/***************Ӳ���ж����ȼ�******************/
#define NVIC_UART_P	5
#define NVIC_UART_S	1
#define NVIC_TIM4_P	2
#define NVIC_TIM4_S	1
/***********************************************/

#include "drv_led.h"
#include "drv_i2c_soft.h"
#include "drv_uart.h"
#include "drv_wifi.h"
#include "drv_motors.h"

void board_Init(void);
void SysTick_IRQ(void);
uint32_t GetSysTime_us(void);


#endif /* __BOARD_H__ */

// 





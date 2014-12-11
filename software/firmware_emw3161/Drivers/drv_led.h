#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "stm32f2xx.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
/***************LED GPIO∂®“Â******************/
#define RCC_AHB1Periph_LED			RCC_AHB1Periph_GPIOF
#define GPIO_LED		GPIOF
#define Pin_LED			GPIO_Pin_9


#define LED_OFF() GPIO_SetBits(GPIO_LED,Pin_LED)
#define LED_ON() GPIO_ResetBits(GPIO_LED,Pin_LED)

void LED_Init(void);
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif



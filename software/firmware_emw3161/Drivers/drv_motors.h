#ifndef __DRV_MOTORS_H_
#define __DRV_MOTORS_H_
#include "stm32f2xx.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
#define Moto_PwmMax 999

void Motors_Init(void);
void Motors_PwmRflash(int32_t MOTO1_PWM,int32_t MOTO2_PWM,int32_t MOTO3_PWM,int32_t MOTO4_PWM);
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

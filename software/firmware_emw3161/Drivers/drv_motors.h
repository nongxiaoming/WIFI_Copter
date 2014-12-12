#ifndef __DRV_MOTORS_H_
#define __DRV_MOTORS_H_
#include "stm32f2xx.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
#define MOTORS_PWM_MAX 2000
#define MOTORS_PWM_MIN 1000
#define MOTORS_NUM_MAX 4
	 
void Motors_Init(void);
void Motors_SetPwm(uint16_t *pwm);
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

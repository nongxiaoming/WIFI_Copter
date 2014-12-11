#ifndef __DRV_I2C_SOFT_H__
#define __DRV_I2C_SOFT_H__


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
#include "stm32f2xx.h"


#define SCL_H         GPIO_SetBits(ANO_GPIO_I2C,I2C_Pin_SCL)
#define SCL_L         GPIO_ResetBits(ANO_GPIO_I2C,I2C_Pin_SCL)
#define SDA_H         GPIO_SetBits(ANO_GPIO_I2C,I2C_Pin_SDA)
#define SDA_L         GPIO_ResetBits(ANO_GPIO_I2C,I2C_Pin_SDA)
#define SCL_read      GPIO_ReadInputDataBit(ANO_GPIO_I2C,I2C_Pin_SCL)
#define SDA_read     GPIO_ReadInputDataBit(ANO_GPIO_I2C,I2C_Pin_SDA)


void I2C_Soft_Init(void);
int I2C_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);	
int I2C_Single_Read(u8 SlaveAddress,u8 REG_Address);
int I2C_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size);

	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 �������ƴ�
 * �ļ���  ��ANO_Param.cpp
 * ����    ��������ȡ�ͱ���
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include <rthw.h>
#include "params.h"
#include "sensor.h"
#include "board.h"



#define PARAMS_SAVE_ADDRESS    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#define PARAMS_SAVE_Sector      FLASH_Sector_11

static params_t *params;
static rt_err_t Params_Read(void);
	 
void Params_Init(void)
{

   params = (params_t*)rt_malloc(sizeof(params_t));
	 if(Params_Read()==RT_EOK)
   {
	  
	 }else
   {
	   Params_Save();
	 }
	
}

void Params_setAccOffset(vector3i_t offset)
{
 params->acc_offset = offset;
}
vector3i_t Params_getAccOffset(void)
{
  return params->acc_offset;
}

void Params_setGyroOffset(vector3i_t offset)
{
 params->gyro_offset = offset;
}
vector3i_t Params_getGyroOffset(void)
{
 return params->gyro_offset;
}

void Params_setRollPid(pid_t val)
{
params->roll_pid = val;
}
pid_t Params_getRollPid(void)
{
 return params->roll_pid;
}

void Params_setPitchPid(pid_t val)
{
params->pitch_pid = val;
}
pid_t Params_getPitchPid(void)
{
 return params->pitch_pid;
}

void Params_setYawPid(pid_t val)
{
params->yaw_pid = val;
}
pid_t Params_getYawPid(void)
{
 return params->yaw_pid;
}

rt_err_t Params_Read(void)
{
  
  rt_memcpy(params,(void*)PARAMS_SAVE_ADDRESS,sizeof(params_t));
	if(params->magic != MAGIC)
  {
	 return RT_ERROR;
	}
	return RT_EOK;
}
void Params_Save(void)
{
	 uint32_t *data;
	 uint32_t address, address_end;
   params->magic = MAGIC;

    /* Unlock the Flash */
    FLASH_Unlock();

    data = (uint32_t *)params;
    address = PARAMS_SAVE_ADDRESS;
    address_end = address + sizeof(params_t);
	  
	      /* Clear pending flags (if any) */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	 
	  FLASH_EraseSector(PARAMS_SAVE_Sector, VoltageRange_3);
	
    while(address < address_end)
    {
        rt_base_t level;
        FLASH_Status status;
        const uint32_t *data_read;

        data_read = (const uint32_t *)address;
        if(*data_read == *data)
        {
            address += 4;
            data++;
            continue;
        }

        level = rt_hw_interrupt_disable();
        status = FLASH_ProgramWord(address, *data);
        rt_hw_interrupt_enable(level);

        if (status == FLASH_COMPLETE)
        {
            address += 4;
            data++;
        }
        else
        {
            rt_kprintf("FLASH 0x%08X program failed!\n", address);
            continue;
        }
    }
    FLASH_Lock();
}










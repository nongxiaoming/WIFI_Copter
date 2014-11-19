/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include <rthw.h>
#include "params.h"
#include "sensor.h"
#include "board.h"

Params params;

#define PARAMS_SAVE_ADDRESS    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#define PARAMS_SAVE_Sector      FLASH_Sector_11

void Params::Init(void)
{

   this->value = (params_t*)rt_malloc(sizeof(params_t));
	 if(this->Read()==RT_EOK)
   {
	  
	 }else
   {
	   this->Save();
	 }
	
}

void Params::set_acc_offset(vector3i_t offset)
{
 this->value->acc_offset = offset;
}
vector3i_t Params::get_acc_offset(void)
{
  return this->value->acc_offset;
}

void Params::set_gyro_offset(vector3i_t offset)
{
 this->value->gyro_offset = offset;
}
vector3i_t Params::get_gyro_offset(void)
{
 return this->value->gyro_offset;
}

void Params::set_roll_pid(pid_t val)
{
this->value->roll_pid = val;
}
pid_t Params::get_roll_pid(void)
{
 return this->value->roll_pid;
}

void Params::set_pitch_pid(pid_t val)
{
this->value->pitch_pid = val;
}
pid_t Params::get_pitch_pid(void)
{
 return this->value->pitch_pid;
}

void Params::set_yaw_pid(pid_t val)
{
this->value->yaw_pid = val;
}
pid_t Params::get_yaw_pid(void)
{
 return this->value->yaw_pid;
}

rt_err_t Params::Read(void)
{
  rt_memcpy(this->value,(void*)PARAMS_SAVE_ADDRESS,sizeof(params_t));
	if(this->value->magic != MAGIC)
  {
	 return RT_ERROR;
	}
	return RT_EOK;
}
void Params::Save(void)
{
	 uint32_t *data;
	 uint32_t address, address_end;
   this->value->magic = MAGIC;

    /* Unlock the Flash */
    FLASH_Unlock();

    data = (uint32_t *)this->value;
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










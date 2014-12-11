/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_Param.cpp
 * 描述    ：参数读取和保存
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "params.h"
//#include "sensor.h"
#include "board.h"



#define PARAMS_SAVE_ADDRESS    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#define PARAMS_SAVE_Sector      FLASH_Sector_11

static params_t params;
static bool Params_Read(void);
	 
void Params_Init(void)
{

	 if(Params_Read()==true)
   {
	  
	 }else
   {
	   Params_Save();
	 }
	
}

void Params_setAccOffset(Vector3i offset)
{
 params.acc_offset = offset;
}
Vector3i Params_getAccOffset(void)
{
  return params.acc_offset;
}

void Params_setGyroOffset(Vector3i offset)
{
 params.gyro_offset = offset;
}
Vector3i Params_getGyroOffset(void)
{
 return params.gyro_offset;
}

void Params_setRollPid(pid_t val)
{
params.roll_pid = val;
}
pid_t Params_getRollPid(void)
{
 return params.roll_pid;
}

void Params_setPitchPid(pid_t val)
{
params.pitch_pid = val;
}
pid_t Params_getPitchPid(void)
{
 return params.pitch_pid;
}

void Params_setYawPid(pid_t val)
{
params.yaw_pid = val;
}
pid_t Params_getYawPid(void)
{
 return params.yaw_pid;
}

bool Params_Read(void)
{
  
  memcpy(&params,(void*)PARAMS_SAVE_ADDRESS,sizeof(params_t));
	if(params.magic != MAGIC)
  {
	 return false;
	}
	return true;
}
void Params_Save(void)
{
	 uint32_t *data;
	 uint32_t address, address_end;
   params.magic = MAGIC;

    /* Unlock the Flash */
    FLASH_Unlock();

    data = (uint32_t *)&params;
    address = PARAMS_SAVE_ADDRESS;
    address_end = address + sizeof(params_t);
	  
	      /* Clear pending flags (if any) */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	 
	  FLASH_EraseSector(PARAMS_SAVE_Sector, VoltageRange_3);
	
    while(address < address_end)
    {
        FLASH_Status status;
        const uint32_t *data_read;

        data_read = (const uint32_t *)address;
        if(*data_read == *data)
        {
            address += 4;
            data++;
            continue;
        }

        
        status = FLASH_ProgramWord(address, *data);
       

        if (status == FLASH_COMPLETE)
        {
            address += 4;
            data++;
        }
        else
        {
            continue;
        }
    }
    FLASH_Lock();
}










#include "rc.h"

void Rc_Fun(T_RC_Data *rc_in,T_Control *rc_ct)
{
	static u8 cnt_arm=0,cnt_fun=0;
	if(rc_in->THROTTLE<RC_FUN_MIN&&rc_in->YAW<RC_FUN_MIN)//½âËø
	{
		cnt_arm++;
		if(cnt_arm==75)
		{
			cnt_arm=0;
			rc_ct->ARMED = 1;
			MPU6050_CalOff_Acc();
			MPU6050_CalOff_Gyr();
		}
	}
	else if(rc_in->THROTTLE<RC_FUN_MIN&&rc_in->YAW>RC_FUN_MAX)//¼ÓËø
	{
		cnt_arm++;
		if(cnt_arm==75)
		{
			cnt_arm=0;
			rc_ct->ARMED = 0;
		}
	}
	else
		cnt_arm = 0;
		
	if(rc_ct->ARMED==1)
		return;
	
	if(rc_in->THROTTLE<RC_FUN_MIN&&rc_in->ROLL<RC_FUN_MIN)
	{
		cnt_fun++;
		if(cnt_fun==75)
		{
			cnt_fun = 0;
			MPU6050_CalOff_Acc();
		}
	}
	else if(rc_in->THROTTLE<RC_FUN_MIN&&rc_in->ROLL>RC_FUN_MAX)
	{
		cnt_fun++;
		if(cnt_fun==75)
		{
			cnt_fun = 0;
			MPU6050_CalOff_Gyr();
		}
	}
	else
		cnt_fun = 0;
}

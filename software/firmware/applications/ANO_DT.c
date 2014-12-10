/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：匿名科创
 * 文件名  ：ANO_DT.cpp
 * 描述    ：无线数据收发和处理
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "ANO_DT.h"
#include "Sensor.h"
#include "pidctrl.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

struct Transmiter dt;

static	u8 data_to_send[50];

static	void Send_Status(void);
static	void Send_Senser(void);
static	void Send_RCData(void);
static	void Send_MotoPWM(void);
static	void Send_PID1(void);
static	void Send_PID2(void);
static	void Send_PID3(void);
static	void Send_Check(u16 check);

static	void Send_Data(u8 *dataToSend , u8 length);

void Transmiter_Data_Anl(u8 *data_buf,u8 num)
{
		u8 i=0;
	u8 sum = 0;
	
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//判断sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//判断帧头
	
	config.failsafe = 0;
/////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0X01)
	{
		if(*(data_buf+4)==0X01)
			sensor.Acc_CALIBRATED = 1;
		if(*(data_buf+4)==0X02)
			sensor.Gyro_CALIBRATED = 1;
		if(*(data_buf+4)==0X03)
		{
			sensor.Acc_CALIBRATED = 1;		
			sensor.Gyro_CALIBRATED = 1;			
		}
	}
	
	if(*(data_buf+2)==0X02)
	{
		if(*(data_buf+4)==0X01)
		{
			dt.Send_PID1 = 1;
			dt.Send_PID2 = 1;
			dt.Send_PID3 = 1;
		}
		if(*(data_buf+4)==0X02)
		{
			
		}
	}

	if(*(data_buf+2)==0X03)
	{
		rc.rawData[THROTTLE] = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		rc.rawData[YAW] = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		rc.rawData[ROLL] = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		rc.rawData[PITCH] = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		rc.rawData[AUX1] = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		rc.rawData[AUX2] = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		rc.rawData[AUX3] = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		rc.rawData[AUX4] = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
	}

	if(*(data_buf+2)==0X10)								//PID1
	{
		pid_group[PIDROLL].kp = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);
		pid_group[PIDROLL].ki = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		pid_group[PIDROLL].kd = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		pid_group[PIDPITCH].kp = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		pid_group[PIDPITCH].ki = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		pid_group[PIDPITCH].kd = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		pid_group[PIDYAW].kp = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		pid_group[PIDYAW].ki= (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
		pid_group[PIDYAW].kd = (vs16)(*(data_buf+20)<<8)|*(data_buf+21);
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X11)								//PID2
	{
		Send_Check(sum);
	}
	if(*(data_buf+2)==0X12)								//PID3
	{
		Send_Check(sum);
		Params_Save();
	}
	if(*(data_buf+2)==0X16)								//OFFSET
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0x18)					
	{

	}
}

void Transmiter_CheckEvent(void)
{
	
#ifdef ANO_DT_USE_NRF24l01	
	nrf.Check_Event();
#endif
	
}

void Transmiter_DataExchange(void)
{
	static u8 cnt = 0;
	
	switch(cnt)
	{
		case 1: 
			dt.Send_RCData = 1;
			break;
		case 2:
			dt.Send_MotoPwm = 1;
			break;
		case 30:
			cnt = 0;
			break;
		default:
			if(cnt%3)
				dt.Send_Senser = 1;	
			else
				dt.Send_Status = 1;
						
	}
	cnt++;
	
	if(dt.Send_Status){
		dt.Send_Status = 0;
		Send_Status();
	}	
	if(dt.Send_Senser){
		dt.Send_Senser = 0;
		Send_Senser();
	}	
	if(dt.Send_RCData){
		dt.Send_RCData = 0;
		Send_RCData();
	}		
	if(dt.Send_MotoPwm){
		dt.Send_MotoPwm = 0;
		Send_MotoPWM();
	}	
	if(dt.Send_PID1){
		dt.Send_PID1 = 0;
		Send_PID1();
	}	
	if(dt.Send_PID2){
		dt.Send_PID2 = 0;
		Send_PID2();
	}	
}

static void Send_Status(void)
{
	u8 _cnt=0;
  u8 i=0;
	u8 sum = 0;
	vs16 _temp;
	vs32 _temp2 = 0;//UltraAlt * 100;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;

	_temp = (int)(imu.angle.x*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(imu.angle.y*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(imu.angle.z*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);

	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}


static void Send_Senser(void)
{
	u8 _cnt=0;
	u8 i=0;
	u8 sum = 0;
	vs16 _temp;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	_temp = imu.Acc.x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = imu.Acc.y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = imu.Acc.z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = Sensor_GetGyro().x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = Sensor_GetGyro().y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = Sensor_GetGyro().z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = 0;
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	Send_Data(data_to_send, _cnt);
}

static void Send_RCData(void)
{
	u8 _cnt=0;
	u8 i=0;
	u8 sum = 0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(rc.rawData[THROTTLE]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[THROTTLE]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[YAW]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[YAW]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[ROLL]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[ROLL]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[PITCH]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[PITCH]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX1]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX1]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX2]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX2]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX3]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX3]);
	data_to_send[_cnt++]=BYTE1(rc.rawData[AUX4]);
	data_to_send[_cnt++]=BYTE0(rc.rawData[AUX4]);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

static void Send_MotoPWM(void)
{
	u8 _cnt=0;
	u8 i=0;
	u8 sum = 0;
	uint16_t Moto_PWM[6];
	
	PIDCtrl_GetPWM(Moto_PWM);
	
	for(i=0;i<6;i++)
		Moto_PWM[i] -= 1000;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(Moto_PWM[1]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[1]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[3]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[3]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[5]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[5]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[2]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[2]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[0]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[0]);
	data_to_send[_cnt++]=BYTE1(Moto_PWM[4]);
	data_to_send[_cnt++]=BYTE0(Moto_PWM[4]);

	data_to_send[3] = _cnt-4;
	
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

static void Send_PID1(void)
{
	u8 _cnt=0;
	u8 i=0;
	u8 sum = 0;
	vs16 _temp;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10;
	data_to_send[_cnt++]=0;
	

	_temp = pid_group[PIDROLL].kp ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDROLL].ki ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDROLL].kd ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDPITCH].kp ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDPITCH].ki ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDPITCH].kd ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDYAW].kp;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDYAW].ki;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = pid_group[PIDYAW].kd;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;

	Send_Data(data_to_send, _cnt);
}

static void Send_PID2(void)
{
	u8 _cnt=0;
	u8 i=0;
	u8 sum = 0;
	vs16 _temp=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x11;
	data_to_send[_cnt++]=0;
	

	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Send_Data(data_to_send, _cnt);
}

static void Send_Check(u16 check)
{
	u8 i=0;
	u8 sum = 0;
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xF0;
	data_to_send[3]=3;
	data_to_send[4]=0xBA;
	
	data_to_send[5]=BYTE1(check);
	data_to_send[6]=BYTE0(check);
	
	for(i=0;i<7;i++)
		sum += data_to_send[i];
	
	data_to_send[7]=sum;

	Send_Data(data_to_send, 8);
}

static void Send_Data(u8 *dataToSend , u8 length)
{
	
#ifdef ANO_DT_USE_Bluetooth
	Uart1_Put_Buf(data_to_send,length);
#endif
	
#ifdef ANO_DT_USE_NRF24l01
	nrf.TxPacket(data_to_send,length);
#endif
}


void Transmiter_FailsafeCheck(void)
{
		static u8 failsafeCnt = 0;
		if(failsafeCnt > 30)
		{
			failsafeCnt = 0;
			if(!config.failsafe)
				config.failsafe = 1;
			else
			{	
				config.ARMED = 0;
			}
		}
		failsafeCnt++;	
}




/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

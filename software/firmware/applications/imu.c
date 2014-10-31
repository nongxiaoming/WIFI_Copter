#include "imu.h"
#include "math.h"


#define RtA 		57.324841f				
#define AtR    		0.0174533f				
#define Acc_G 		0.0011963f				
#define Gyro_G 		0.0610351f				
#define Gyro_Gr		0.0010653f			
#define FILTER_NUM 	20

float 	AngleOffset_Rol=0,AngleOffset_Pit=0;

void Prepare_Data(rt_axes3i_t *acc_in,rt_axes3i_t *acc_out)
{
	static uint8_t 	filter_cnt=0;
	static int16_t	ACC_X_BUF[FILTER_NUM],ACC_Y_BUF[FILTER_NUM],ACC_Z_BUF[FILTER_NUM];
	int32_t temp1=0,temp2=0,temp3=0;
	uint8_t i;

	ACC_X_BUF[filter_cnt] = acc_in->x;
	ACC_Y_BUF[filter_cnt] = acc_in->y;
	ACC_Z_BUF[filter_cnt] = acc_in->z;
	for(i=0;i<FILTER_NUM;i++)
	{
		temp1 += ACC_X_BUF[i];
		temp2 += ACC_Y_BUF[i];
		temp3 += ACC_Z_BUF[i];
	}
	acc_out->x = temp1 / FILTER_NUM;
	acc_out->y = temp2 / FILTER_NUM;
	acc_out->z = temp3 / FILTER_NUM;
	filter_cnt++;
	if(filter_cnt==FILTER_NUM)	filter_cnt=0;
	
}
////////////////////////////////////////////////////////////////////////////////
#define Kp 1.0f                        // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.001f                          // integral gain governs rate of convergence of gyroscope biases
#define halfT 0.001f                   // half the sample period???????

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;    // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error
void IMUupdate(rt_axes3i_t *gyr, rt_axes3i_t *acc, rt_angle3f_t *angle)
{
	float ax = acc->x,ay = acc->y,az = acc->z;
	float gx = gyr->x,gy = gyr->y,gz = gyr->z;
  float norm;
//  float hx, hy, hz, bx, bz;
  float vx, vy, vz;// wx, wy, wz;
  float ex, ey, ez;

  // ???????????
  float q0q0 = q0*q0;
  float q0q1 = q0*q1;
  float q0q2 = q0*q2;
//  float q0q3 = q0*q3;
  float q1q1 = q1*q1;
//  float q1q2 = q1*q2;
  float q1q3 = q1*q3;
  float q2q2 = q2*q2;
  float q2q3 = q2*q3;
  float q3q3 = q3*q3;
	
	if(ax*ay*az==0)
 		return;
		
	gx *= Gyro_Gr;
	gy *= Gyro_Gr;
	gz *= Gyro_Gr;
		
  norm = sqrt(ax*ax + ay*ay + az*az);       //acc?????
  ax = ax /norm;
  ay = ay / norm;
  az = az / norm;

  // estimated direction of gravity and flux (v and w)              ?????????/??
  vx = 2*(q1q3 - q0q2);												//????xyz???
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;

  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy) ;                           					 //???????????????
  ey = (az*vx - ax*vz) ;
  ez = (ax*vy - ay*vx) ;

  exInt = exInt + ex * Ki;								  //???????
  eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;

  // adjusted gyroscope measurements
  gx = gx + Kp*ex + exInt;					   							//???PI???????,???????
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;				   							//???gz????????????????,??????????????

  // integrate quaternion rate and normalise						   //????????
  q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

  // normalise quaternion
  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;

  angle->yaw += gyr->z*Gyro_G*0.002;//atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.3; // yaw
  angle->roll = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3 - AngleOffset_Pit; // pitch
  angle->pitch = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3 - AngleOffset_Rol; // roll
}

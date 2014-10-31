#ifndef __SENSOR_H
#define __SENSOR_H

#include <rtthread.h>

typedef struct
{
 rt_int16_t x;
 rt_int16_t y;
 rt_int16_t z;
}rt_axes3i_t;

typedef struct
{
 float x;
 float y;
 float z;
}rt_axes3f_t;

typedef struct
{
 float roll;
 float pitch;
 float yaw;
}rt_angle3f_t;


#endif

#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>

struct Quaternion
{
    float        q1, q2, q3, q4;

//    // 构造函数
//    // roll=0, pitch=0, yaw=0
//    Quaternion() {
//        q1 = 1; q2 = q3 = q4 = 0;
//    }

//    //赋值构造函数
//    Quaternion(const float _q1, const float _q2, const float _q3, const float _q4) :
//        q1(_q1), q2(_q2), q3(_q3), q4(_q4) {
//    }

//    //函数调用操作符
//    void operator        ()(const float _q1, const float _q2, const float _q3, const float _q4)
//    {
//        q1 = _q1; q2 = _q2; q3 = _q3; q4 = _q4;
//    }
		

};
//四元数归一化
void Quaternion_normalize(struct Quaternion *Q);

 // 返回该四元数的等效旋转矩阵中的重力分量
void Quaternion_vector_gravity(struct Quaternion Q,vector3f_t *v);

//一阶龙格库塔法更新四元数
void Quaternion_Runge_Kutta_1st(struct Quaternion *Q,vector3f_t *g, float deltaT);
		
//欧拉角转四元数
void Quaternion_fromEuler(struct Quaternion *Q,float roll, float pitch, float yaw);

 //四元数转欧拉角
void Quaternion_toEuler(struct Quaternion Q,float *roll, float *pitch, float *yaw);

#endif // QUATERNION_H















#include "ANO_Math.h"


// 返回该四元数的等效旋转矩阵中的重力分量
void Quaternion_vector_gravity(struct Quaternion Q,vector3f_t *v)
{
  v->x = 2*(Q.q2*Q.q4 - Q.q1*Q.q3);								
  v->y = 2*(Q.q1*Q.q2 + Q.q3*Q.q4);						  
  v->z = 1-2*(Q.q2*Q.q2 + Q.q3*Q.q3);
}

//四元数归一化
void Quaternion_normalize(struct Quaternion *Q)
{
	float length; 
	length= pythagorous4(Q->q1, Q->q2, Q->q3, Q->q4);
	Q->q1 /= length;
	Q->q2 /= length;
	Q->q3 /= length;
	Q->q4 /= length;
}

//一阶龙格库塔法更新四元数
void Quaternion_Runge_Kutta_1st(struct Quaternion *Q,vector3f_t *g, float deltaT)
{
  Q->q1 += 0.5 * (-Q->q2*g->x - Q->q3*g->y - Q->q4*g->z)* deltaT;
  Q->q2 += 0.5 * (Q->q1*g->x + Q->q3*g->z - Q->q4*g->y)* deltaT;
  Q->q3 += 0.5 * (Q->q1*g->y - Q->q2*g->z + Q->q4*g->x)* deltaT;
  Q->q4 += 0.5 * (Q->q1*g->z + Q->q2*g->y - Q->q3*g->x)* deltaT;	
}

//欧拉角转四元数
void Quaternion_fromEuler(struct Quaternion *Q,float roll, float pitch, float yaw)
{
    float cr2 = cosf(roll*0.5f);
    float cp2 = cosf(pitch*0.5f);
    float cy2 = cosf(yaw*0.5f);
    float sr2 = sinf(roll*0.5f);
    float sp2 = sinf(pitch*0.5f);
    float sy2 = sinf(yaw*0.5f);

    Q->q1 = cr2*cp2*cy2 + sr2*sp2*sy2;
    Q->q2 = sr2*cp2*cy2 - cr2*sp2*sy2;
    Q->q3 = cr2*sp2*cy2 + sr2*cp2*sy2;
    Q->q4 = cr2*cp2*sy2 - sr2*sp2*cy2;
}

//四元数转欧拉角
void Quaternion_toEuler(struct Quaternion Q,float *roll, float *pitch, float *yaw)
{
    if (roll) {
        *roll = degrees(atan2f(2.0f*(Q.q1*Q.q2 + Q.q3*Q.q4),1 - 2.0f*(Q.q2*Q.q2 + Q.q3*Q.q3)));
    }
    if (pitch) {
        // 使用safe_asin()来处理pitch接近90/-90时的奇点
        *pitch = degrees(safe_asin(2.0f*(Q.q1*Q.q3 - Q.q2*Q.q4)));
    }
    if (yaw) {
        *yaw = degrees(atan2f(2.0f*(Q.q2*Q.q3 - Q.q1*Q.q4), 2.0f*(Q.q1*Q.q1 + Q.q2*Q.q2) - 1));
    }
}










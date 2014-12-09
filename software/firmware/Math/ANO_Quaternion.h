#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>

struct Quaternion
{
    float        q1, q2, q3, q4;

//    // ���캯��
//    // roll=0, pitch=0, yaw=0
//    Quaternion() {
//        q1 = 1; q2 = q3 = q4 = 0;
//    }

//    //��ֵ���캯��
//    Quaternion(const float _q1, const float _q2, const float _q3, const float _q4) :
//        q1(_q1), q2(_q2), q3(_q3), q4(_q4) {
//    }

//    //�������ò�����
//    void operator        ()(const float _q1, const float _q2, const float _q3, const float _q4)
//    {
//        q1 = _q1; q2 = _q2; q3 = _q3; q4 = _q4;
//    }
		

};
//��Ԫ����һ��
void Quaternion_normalize(struct Quaternion *Q);

 // ���ظ���Ԫ���ĵ�Ч��ת�����е���������
void Quaternion_vector_gravity(struct Quaternion Q,vector3f_t *v);

//һ�����������������Ԫ��
void Quaternion_Runge_Kutta_1st(struct Quaternion *Q,vector3f_t *g, float deltaT);
		
//ŷ����ת��Ԫ��
void Quaternion_fromEuler(struct Quaternion *Q,float roll, float pitch, float yaw);

 //��Ԫ��תŷ����
void Quaternion_toEuler(struct Quaternion Q,float *roll, float *pitch, float *yaw);

#endif // QUATERNION_H















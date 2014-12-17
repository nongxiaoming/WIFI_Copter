#ifndef __ANO_RC_H
#define __ANO_RC_H

#include "config.h"

#define RC_MID  			1500                     
#define RC_MINCHECK		1150                      
#define RC_MAXCHECK  	1850 

enum {
    ROLL = 0,
    PITCH,
    YAW,
    THROTTLE,
    AUX1,
    AUX2,
    AUX3,
    AUX4,
		AUX5,
		AUX6
};

class ANO_RC
{
	
public:
	
	ANO_RC();

	uint16_t rawData[10];
	int16_t Command[4];

	//������ʼ��
	void Init(void);
	//ң��ͨ�����ݴ���
	void Cal_Command(void);
	//ҡ��λ�ü��
	void check_sticks(void);

private:

};

extern ANO_RC rc;

#endif




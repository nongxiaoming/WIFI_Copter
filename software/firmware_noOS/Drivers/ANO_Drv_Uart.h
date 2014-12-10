#ifndef __ANO_DRV_UART_H__
#define __ANO_DRV_UART_H__

#include "board.h"

class ANO_UART1
{
public:
	static void Uart1_Init(u32 br_num);
	void Uart1_IRQ(void);
	void Uart1_Put_String(unsigned char *Str);
	void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num);
};

extern ANO_UART1 uart1;

#endif

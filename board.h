#ifndef	__BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#define ABS(a)      (a>0 ? a:(-a))
extern int32_t Get_Encoder_countA,Get_Encoder_countB;


void delay_us(unsigned long __us);
void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);

void uart0_send_char(char ch);
void uart0_send_string(char* str);

void Serial_JY61P_Zero_Yaw(void);
void Serial_JY61P_XY_Yaw(void);
#endif

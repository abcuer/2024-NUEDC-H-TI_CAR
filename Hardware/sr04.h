/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-01     LCKFB-LP    first version
 */

#ifndef _sr04_h
#define _sr04_h


#include "board.h"

#define SR04_TRIG(x)  ( x ? DL_GPIO_setPins(SR04_PORT,SR04_Trig_PIN) : DL_GPIO_clearPins(SR04_PORT,SR04_Trig_PIN) )
#define SR04_ECHO()   ( ( ( DL_GPIO_readPins(SR04_PORT,SR04_Echo_PIN) & SR04_Echo_PIN ) > 0 ) ? 1 : 0 )

void Ultrasonic_Init(void);//��������ʼ��
float Hcsr04GetLength(void );//��ȡ���������ľ���

#endif

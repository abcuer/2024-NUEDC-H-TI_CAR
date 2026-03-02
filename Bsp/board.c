/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version
 */
#include "board.h"

#include "stdint.h"

//void delay_us(unsigned long __us)
//{
//    uint32_t ticks;
//    uint32_t told, tnow, tcnt = 38;

//    ticks = __us * (32000000 / 1000000);

//    told = SysTick->VAL;

//    while (1)
//    {
//        tnow = SysTick->VAL;

//        if (tnow != told)
//        {
//            if (tnow < told)
//                tcnt += told - tnow;
//            else
//                tcnt += SysTick->LOAD - tnow + told;

//            told = tnow;

//            if (tcnt >= ticks)
//                break;
//        }
//    }
//}

//void delay_ms(unsigned long ms)
//{
//    delay_us(ms * 1000);
//}





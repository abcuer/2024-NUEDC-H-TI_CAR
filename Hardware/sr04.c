#include "headfile.h"

volatile unsigned int msHcCount = 0;//ms����
volatile float utl_dist = 0;

/******************************************************************
 * �� �� �� �ƣ�bsp_ultrasonic
 * �� �� ˵ ������������ʼ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��TRIG���Ÿ����ͳ��������崮
******************************************************************/
void Ultrasonic_Init(void)
{

    //�����ʱ���жϱ�־
    NVIC_ClearPendingIRQ(TIMER_2_INST_INT_IRQN);
    //ʹ�ܶ�ʱ���ж�
    NVIC_EnableIRQ(TIMER_2_INST_INT_IRQN);

}
/******************************************************************
 * �� �� �� �ƣ�Open_Timer
 * �� �� ˵ �����򿪶�ʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��
******************************************************************/
void Open_Timer(void)
{

    DL_TimerA_setTimerCount(TIMER_2_INST, 0);   // �����ʱ������

    msHcCount = 0;

    DL_TimerA_startCounter(TIMER_2_INST);   // ʹ�ܶ�ʱ��
}

/******************************************************************
 * �� �� �� �ƣ�Get_TIMER_Count
 * �� �� ˵ ������ȡ��ʱ����ʱʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ�����
 * ��       �ߣ�LC
 * ��       ע��
******************************************************************/
uint32_t Get_TIMER_Count(void)
{
    uint32_t time  = 0;
    time   = msHcCount*1000;                         // �õ�us
    time  += DL_TimerA_getTimerCount(TIMER_2_INST);  // �õ�ms

    DL_TimerA_setTimerCount(TIMER_2_INST, 0);   // �����ʱ������
    delay_ms(1);
    return time ;
}

/******************************************************************
 * �� �� �� �ƣ�Close_Timer
 * �� �� ˵ �����رն�ʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��
******************************************************************/
void Close_Timer(void)
{
    DL_TimerA_stopCounter(TIMER_2_INST);     // �رն�ʱ��
}

/******************************************************************
 * �� �� �� �ƣ�TIMER_2_INST_IRQHandler
 * �� �� ˵ ������ʱ���жϷ�����
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��1ms����һ��
******************************************************************/
void TIMER_2_INST_IRQHandler(void)
{
    // ��ȡ��ǰ�ж��������
   if(DL_TimerA_getPendingInterrupt(TIMER_2_INST))
	{
		if(DL_TIMER_IIDX_ZERO) 
		{	
			msHcCount++;
		}
	}
}

/******************************************************************
 * �� �� �� �ƣ�Hcsr04GetLength
 * �� �� ˵ ������ȡ��������
 * �� �� �� �Σ���
 * �� �� �� �أ���������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
volatile float t = 0;
float Hcsr04GetLength(void)
{
        /*��5�����ݼ���һ��ƽ��ֵ*/
        volatile float length = 0;
		t = 0;
        volatile float sum = 0;
        volatile unsigned int  i = 0;

		Close_Timer();

//        while(i != 3)  // ���ٲ����������ӿ�Ƶ��
//		{
			SR04_TRIG(0);
			delay_1us(10);
			SR04_TRIG(1);
			delay_1us(15);
			SR04_TRIG(0);

			while(SR04_ECHO() == 0);  // �ȴ����쿪ʼ
			Open_Timer();
			i++;
			while(SR04_ECHO() > 0);   // �ȴ��������
			Close_Timer();

			delay_ms(6);  // ���̵ȴ����

			t = (float)Get_TIMER_Count();
			length = t / 58.0f;  // ����(cm)
			sum += length;
//		}
        length = sum;//���ƽ��ֵ
        utl_dist = length;
        return length;
}
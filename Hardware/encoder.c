#include "encoder.h"

float Get_Encoder_countA = 0;
float Get_Encoder_countB = 0;

/*
		E1A E1B: Get_Encoder_countA
		Pin: A09 A08
		E2A E2B: Get_Encoder_countB  
		Pin: B07 B08
*/

void encoder_Init(void)
{
	NVIC_ClearPendingIRQ(Encoder_left_INT_IRQN);
	NVIC_ClearPendingIRQ(Encoder_right_INT_IRQN);
	NVIC_EnableIRQ(Encoder_left_INT_IRQN);
	NVIC_EnableIRQ(Encoder_right_INT_IRQN);
}

/*******************************************************
�������ܣ��ⲿ�ж�ģ��������ź�
��ں�������
����  ֵ����
***********************************************************/

void GROUP1_IRQHandler(void)
{
	uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_left_E1A_PIN | Encoder_left_E1B_PIN );
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB, Encoder_right_E2A_PIN | Encoder_right_E2B_PIN);

	// A编码器
	if ((gpioA & Encoder_left_E1A_PIN) == Encoder_left_E1A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1B_PIN))
		{
				Get_Encoder_countA--;
		}
		else
		{
				Get_Encoder_countA++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT, Encoder_left_E1A_PIN);
	}
	
	else if ((gpioA & Encoder_left_E1B_PIN) == Encoder_left_E1B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1A_PIN))
		{
				Get_Encoder_countA++;
		}
		else
		{
				Get_Encoder_countA--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT,Encoder_left_E1B_PIN);
	}
	
	// B编码器
	if ((gpioB & Encoder_right_E2A_PIN) == Encoder_right_E2A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2B_PIN))
		{
				Get_Encoder_countB--;
		}
		else
		{
				Get_Encoder_countB++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2A_PIN);
	}
	else if ((gpioB & Encoder_right_E2B_PIN) == Encoder_right_E2B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2A_PIN))
		{
				Get_Encoder_countB++;
		}
		else
		{
				Get_Encoder_countB--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2B_PIN);
	}
}

#define PI 3.14159265

int One_Wheel_len = 204;		 //mm  һ�ֳ���
int One_Wheel_Mai = 730;   	//һȦ������
float Wheel_count = 0.2794; //mm һ��������ת����
float carL_dis = 0;
float carR_dis = 0;

float dis3 = 1042;  // 1149 - 1151
float dis4 = 996; 

void distance(void)
{
	carR_dis = Wheel_count * -Get_Encoder_countB;
	carL_dis = Wheel_count * Get_Encoder_countA;
}


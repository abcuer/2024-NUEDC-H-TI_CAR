#include "encoder.h"
#include "led.h"
uint32_t gpio_interrup;



/*******************************************************
函数功能：外部中断模拟编码器信号
入口函数：无
返回  值：无
***********************************************************/
void GROUP1_IRQHandler(void)
{
	//使用我司D153C驱动模块时，E1A连接PA15、E1B连接PA16、E2A连接PA17，E2B连接PA22
	//获取中断信号
	gpio_interrup = DL_GPIO_getEnabledInterruptStatus(GPIOA,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN|ENCODERB_E2A_PIN|ENCODERB_E2B_PIN);
	//encoderA
	if((gpio_interrup & ENCODERA_E1A_PIN)==ENCODERA_E1A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOA,ENCODERA_E1B_PIN))
		{
			Get_Encoder_countA--;
		}
		else
		{
			Get_Encoder_countA++;
		}
	}
	else if((gpio_interrup & ENCODERA_E1B_PIN)==ENCODERA_E1B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOA,ENCODERA_E1A_PIN))
		{
			Get_Encoder_countA++;
		}
		else
		{
			Get_Encoder_countA--;
		}
	}
	//encoderB
	if((gpio_interrup & ENCODERB_E2A_PIN)==ENCODERB_E2A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOA,ENCODERB_E2B_PIN))
		{
			Get_Encoder_countB--;
		}
		else
		{
			Get_Encoder_countB++;
		}
	}
	else if((gpio_interrup & ENCODERB_E2B_PIN)==ENCODERB_E2B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOA,ENCODERB_E2A_PIN))
		{
			Get_Encoder_countB++;
		}
		else
		{
			Get_Encoder_countB--;
		}
	}
	DL_GPIO_clearInterruptStatus(GPIOA,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN|ENCODERB_E2A_PIN|ENCODERB_E2B_PIN);
}

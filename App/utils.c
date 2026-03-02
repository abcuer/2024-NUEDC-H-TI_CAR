#include "headfile.h"

uint8_t task_num = 0;
uint8_t start_flag = 0;
uint8_t first_flag = 0;
float basespeed = 0;

void System_Init(void)
{
	SYSCFG_DL_init();
	UartDeviceInit();
	EncoderInit();
	TimerDeviceInit();
}

void TaskSelect(void)
{
	uint8_t Key1 = Key_GetNum1();
	uint8_t Key2 = Key_GetNum2();
		
	// ????
	if(start_flag == 0)
	{
		if (Key1 == 1) 
		{
			LED_Green_ON();
			task_num++;
		}
		if (task_num > 4) task_num = 0; 
	}
	if(Key2 == 1)
	{
		LED_Blue_ON();
		start_flag = 1;
	}

	// 任务执行
	if(start_flag == 1)
	{
		if(first_flag == 1)
		{
			switch(task_num)
			{
				case 1: Task_1(); break;
				case 2: Task_2(); break;
				case 3: Task_3(); break;
				case 4: Task_4(); break;
			}
		}
	}
}


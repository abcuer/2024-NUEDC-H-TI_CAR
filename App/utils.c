#include "headfile.h"

uint8_t task_num = 0;	 // 轮到的任务
uint8_t start_flag = 0;	 // 任务启动标志
uint8_t first_flag = 0;	 // 执行任务前需要完成的操作

void System_Init(void)
{
	SYSCFG_DL_init();
	UartDeviceInit();
	EncoderInit();
	LedDeviceInit();
	BeepDeviceInit();
	KeyDeviceInit();
	TimerDeviceInit();
}

void TaskSelect(void)
{
	if(start_flag == 0)
	{
		if (Key_GetNum(KEY_TASK)) 
		{
			task_num++;
			if (task_num > 4) task_num = 0; 
			SetLedMode(LED_GREEN, LED_ON);
		}
	}
	if(Key_GetNum(KEY_START))
	{
		SetLedMode(LED_BLUE, LED_ON);
		start_flag = 1;
	}

	// 任务执行
	if(start_flag == 1)
	{
		if(first_flag == 1)
		{
			switch(task_num)
			{
				case First: 		FirstTask(); 		break;
				case Second: 	SecondTask(); 	break;
				case Third: 		ThirdTask(); 		break;
				case Fourth: 		FourthTask(); 	break;
			}
		}
	}
}


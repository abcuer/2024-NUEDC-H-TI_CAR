/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "headfile.h"

uint8_t Key1 = 0;
uint8_t Key2 = 0;
uint8_t Task = 0;
uint8_t start_flag = 0;
uint8_t first_flag = 0;
float basespeed = 0;

int main(void)
{
	board_init(); // 延迟 串口
	encoder_Init();
	timerA_init();
	timerG_init();

	// 寻迹环
	while(1) 
	{   
		Key1 = Key_GetNum1();
		Key2 = Key_GetNum2();
		
		// 切换任务
		if(start_flag == 0)
		{
			if (Key1 == 1) 
			{
				LED_Green_ON();
				Task++;
			}
			if (Task > 4) Task = 0; 
		}
		if(Key2 == 1)
		{
			LED_Blue_ON();
			start_flag = 1;
		}
    
		// 执行任务
		if(start_flag == 1)
		{
			if(first_flag == 1)
			{
				switch(Task)
				{
					case 1: Task_1(); break;
					case 2: Task_2(); break;
					case 3: Task_3(); break;
					case 4: Task_4(); break;
				}
			}
		}
		
	}
}


// pid控制
void TIMER_0_INST_IRQHandler(void)
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		if(DL_TIMER_IIDX_ZERO) 
		{	
			Gray_Init();
			speed_pid_control();
		}
	}
}

void TIMER_1_INST_IRQHandler(void)
{
	if(DL_TimerG_getPendingInterrupt(TIMER_1_INST))
	{
		if(DL_TIMER_IIDX_LOAD)
		{	
			// 初始化
			if (start_flag == 1 && first_flag == 0)   initialize();
			UpdateSoundLight();
		}
	}
}




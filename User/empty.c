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


uint8_t Task = 0;
uint8_t start_flag = 0;
uint8_t first_flag = 0;
float basespeed = 0;
uint8_t time_10ms = 0;

float ypr[3];          // 上传yaw pitch roll的值
 extern uint32_t nowtime;

int main(void)
{
	unsigned char buff[10] = {0};
	board_init(); // 延迟 串口
	jy901s_Init();
	delay_ms(100);//等待部署
	IMU_init();
	timer3_init();
	delay_ms(20);
	OLED_Init();
	HC05_Init();
	
	encoder_Init();
	timer0_init();
	timer1_init();
//	Ultrasonic_Init();
	//SPI 模式接线
// PA10------------------------MISO
// PB17------------------------MOSI
// PA11------------------------SCLK
// PA29------------------------CS
	
	while(1) 
	{   
		IMU_getYawPitchRoll(ypr);
        printf("%.2f, %.2f, %.2f\r\n",ypr[0]-20.78,ypr[1],ypr[2]);
        delay_ms(10);
//		test();
//		if(time_10ms)
//		{
//			test();
//			time_10ms = 0;
//		}
	//	Task_select();
	}
}


// pid控制
void TIMER_0_INST_IRQHandler(void)
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		if(DL_TIMER_IIDX_ZERO) 
		{	
			PID_select();
			Key_Tick();
			time_10ms = 1;
		}
	}
}

void TIMER_1_INST_IRQHandler(void)
{
	if(DL_TimerG_getPendingInterrupt(TIMER_1_INST))
	{
		if(DL_TIMER_IIDX_LOAD)
		{	
			if (start_flag == 1 && first_flag == 0)   capture_initial_yaw();
			UpdateSoundLight();
		}
	}
}


void TIMER_3_INST_IRQHandler(void)
{
	switch(DL_TimerG_getPendingInterrupt(TIMER_3_INST))
	{
		case DL_TIMER_IIDX_ZERO:
			nowtime++;
			LED_Blue_ON();
			DL_TimerG_clearInterruptStatus(TIMER_3_INST, DL_TIMER_IIDX_ZERO);
		break;
		default:
			
		break;
	}
}

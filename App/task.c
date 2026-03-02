#include "headfile.h"
#define TimeLimit 11900

uint8_t workstep = 0;
int16_t turn_time = 0;
uint8_t turn_flag = 0;
uint8_t Task4_CNT = 0;

// Task4
float angle3 = -44;  
float angle4 = 52;  

void Task_1(void)
{
	switch(workstep)
	{
		case 0:
			Line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			PID_Init(&angle_pid, POSITION_PID, -8, 0, -0);
			basespeed = 400;
			while(Line_flag == 0)
			{				
				Gray_ProcessLine();
				AnglePidCtrl(ang_offset);
			}
			workstep++;
			break;
			
		case 2:  // 停车
			SoundLightRun();
			basespeed = 0;
			Motor_Stop();
			if(Line_flag)
			{	
				task_num = 0; 
				first_flag = 0;
				start_flag = 0;
				Line_flag = 0;
				
				workstep = 0;
			}
			break;
	}
}

void Task_2(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Init(&track_pid, POSITION_PID, 4.8, 0, 0);
			PID_Init(&angle_pid, POSITION_PID, -8, 0, -0);
			Line_flag = 0;
			basespeed = 400;
			workstep++;
			break;
		
		case 1:  // 直行
			while(Line_flag == 0)
			{				
				Gray_ProcessLine();
				AnglePidCtrl(ang_offset);
			}
			workstep++;
			break;
		
		case 2: // 寻迹
			SoundLightRun();
			basespeed = 390;
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep++;
			break;
			
		case 3: // 直行
			SoundLightRun();
			basespeed = 400;
			while(Line_flag == 0)
			{				
				Gray_ProcessLine();
				AnglePidCtrl(ang_offset);
			}
			workstep++;
			break;
			
		case 4: // 寻迹
			SoundLightRun();
			basespeed = 390;
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			SoundLightRun();
			workstep++;
			break;
			
		case 5:	
			basespeed = 0;
			Motor_Stop();
			delay_ms(100);
			baisetime = 0;
			turn_time = 0;
			turn_flag = 0;
			task_num = 0; 
			first_flag = 0;
			start_flag = 0;
			Line_flag = 0;
			workstep = 0;
			break;	
	}
}

void Task_3(void)
{
		switch(workstep)
	{
		case 0: 
			Line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			turn_flag = 1;
			PID_Init(&angle_pid, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				AnglePidCtrl(angle3);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			basespeed = 480;
			while((fabsf(carL_dis) <= dis3) && (fabsf(carR_dis) <= dis3))
			{
				AnglePidCtrl(angle3);
				Car_GetDistance();
			}
			while(Line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(7);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLightRun();
			// 寻迹			
			basespeed = 390;
			PID_Init(&track_pid, POSITION_PID, 4.8, 0, 0);
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLightRun();
			basespeed = 0;
			turn_flag = 1;
			while(turn_flag)
			{
				AnglePidCtrl(angle4);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			basespeed = 480;
			while((fabsf(carL_dis) <= dis4) && (fabsf(carR_dis) <= dis4))
			{
				AnglePidCtrl(angle4);
				Car_GetDistance();
			}
			PID_Init(&angle_pid, POSITION_PID, -7, 0, -0);
			while(Line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(-1);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLightRun();
			basespeed = 390;
			PID_Init(&track_pid, POSITION_PID, 4.7, 0, 0);
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLightRun(); 
			Motor_Stop();
			delay_ms(100);
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			baisetime = 0;
			turn_time = 0;
			turn_flag = 0;
			task_num = 0; 
			first_flag = 0;
			start_flag = 0;
			Line_flag = 0;
			basespeed = 0;
			workstep = 0;
			break;	
	}
}

void Task_4(void)
{
	switch(workstep)
	{
		case 0: 
			Line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			turn_flag = 1;
			PID_Init(&angle_pid, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				AnglePidCtrl(angle3);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			basespeed = 480;
			while((fabsf(carL_dis) <= dis3) && (fabsf(carR_dis) <= dis3))
			{
				AnglePidCtrl(angle3);
				Car_GetDistance();
			}
			while(Line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(7);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLightRun();
			// 寻迹		
			basespeed = 390;
			PID_Init(&track_pid, POSITION_PID, 4.8, 0, 0);
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLightRun();
			basespeed = 0;
			turn_flag = 1;
			while(turn_flag)
			{
				AnglePidCtrl(angle4);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			basespeed = 480;
			while((fabsf(carL_dis) <= dis4) && (fabsf(carR_dis) <= dis4))
			{
				AnglePidCtrl(angle4);
				Car_GetDistance();
			}
			PID_Init(&angle_pid, POSITION_PID, -7, 0, -0);
			while(Line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(-1);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLightRun();
			basespeed = 390;
			PID_Init(&track_pid, POSITION_PID, 4.7, 0, 0);
			while(Line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLightRun();
			Task4_CNT++;
			Line_flag = 0;
			angle3 = -44;
			angle4 = 51;
			dis3 = 995;
			dis4 = 998;
			if(Task4_CNT == 1)
			{
				dis3 = 992;
//				angle3++;
			}
			if(Task4_CNT == 2)
			{
				angle3--;
//				angle4--;
				dis3 = 994;
				dis4--;
			}
			if(Task4_CNT == 3)
			{
				angle3--;
				angle4--;
				dis3-=2;
//				dis4--;
			}
			if(Task4_CNT < 4) 
			{   // 标志位判断
				baisetime = 0;
				workstep = 0; // 重置工作步骤到case0
			} 
			else if(Task4_CNT >= 4)
			{
				// 停车操作
				Motor_Stop();
				Task4_CNT = 0;
				basespeed = 0;
				workstep = 0;
				task_num = 0; 
				first_flag = 0;
				start_flag = 0;
				delay_ms(100);
			}
			break;	
	}
}


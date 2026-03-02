#include "headfile.h"
#define TimeLimit 11900

uint8_t workstep = 0; // 工作步骤
float basespeed = 0;	// 小车行驶速度
int16_t turn_time = 0;	// 拐角转弯的时间
uint8_t turn_flag = 0;	// 是否启动拐角转弯

// Task4
float angle3 = -44;  
float angle4 = 52;  
float dis3 = 1042;  // 1149 - 1151
float dis4 = 996; 
uint8_t lap_cnt = 0;	// 任务4记录圈数

void FirstTask(void)
{
	switch(workstep)
	{
		case 0:
			line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			PID_Update(&angle_pid, POSITION_PID, -8, 0, -0);
			basespeed = 400;
			while(line_flag == 0)
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
			if(line_flag)
			{	
				task_num = 0; 
				first_flag = 0;
				start_flag = 0;
				line_flag = 0;
				
				workstep = 0;
			}
			break;
	}
}

void SecondTask(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Update(&track_pid, POSITION_PID, 4.8, 0, 0);
			PID_Update(&angle_pid, POSITION_PID, -8, 0, 0);
			line_flag = 0;
			basespeed = 400;
			workstep++;
			break;
		
		case 1:  // 直行
			while(line_flag == 0)
			{				
				Gray_ProcessLine();
				AnglePidCtrl(ang_offset);
			}
			workstep++;
			break;
		
		case 2: // 寻迹
			SoundLightRun();
			basespeed = 390;
			while(line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep++;
			break;
			
		case 3: // 直行
			SoundLightRun();
			basespeed = 400;
			while(line_flag == 0)
			{				
				Gray_ProcessLine();
				AnglePidCtrl(ang_offset);
			}
			workstep++;
			break;
			
		case 4: // 寻迹
			SoundLightRun();
			basespeed = 390;
			while(line_flag)
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
			white_time = 0;
			turn_time = 0;
			turn_flag = 0;
			task_num = 0; 
			first_flag = 0;
			start_flag = 0;
			line_flag = 0;
			workstep = 0;
			break;	
	}
}

void ThirdTask(void)
{
		switch(workstep)
	{
		case 0: 
			line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			turn_flag = 1;
			PID_Update(&angle_pid, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				AnglePidCtrl(angle3);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					white_time = 0;
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
			while(line_flag == 0)
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
			PID_Update(&track_pid, POSITION_PID, 4.8, 0, 0);
			while(line_flag)
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
					white_time = 0;
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
			PID_Update(&angle_pid, POSITION_PID, -7, 0, -0);
			while(line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(-1);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLightRun();
			basespeed = 390;
			PID_Update(&track_pid, POSITION_PID, 4.7, 0, 0);
			while(line_flag)
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
			white_time = 0;
			turn_time = 0;
			turn_flag = 0;
			task_num = 0; 
			first_flag = 0;
			start_flag = 0;
			line_flag = 0;
			basespeed = 0;
			workstep = 0;
			break;	
	}
}

void FourthTask(void)
{
	switch(workstep)
	{
		case 0: 
			line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			turn_flag = 1;
			PID_Update(&angle_pid, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				AnglePidCtrl(angle3);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					white_time = 0;
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
			while(line_flag == 0)
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
			PID_Update(&track_pid, POSITION_PID, 4.8, 0, 0);
			while(line_flag)
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
					white_time = 0;
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
			PID_Update(&angle_pid, POSITION_PID, -7, 0, -0);
			while(line_flag == 0)
			{
				Gray_ProcessLine();
				AnglePidCtrl(-1);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLightRun();
			basespeed = 390;
			PID_Update(&track_pid, POSITION_PID, 4.7, 0, 0);
			while(line_flag)
			{
				Gray_ProcessLine();
				TrackPidCtrl();
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLightRun();
			lap_cnt++;
			line_flag = 0;
			angle3 = -44;
			angle4 = 51;
			dis3 = 995;
			dis4 = 998;
			if(lap_cnt == 1)
			{
				dis3 = 992;
//				angle3++;
			}
			if(lap_cnt == 2)
			{
				angle3--;
//				angle4--;
				dis3 = 994;
				dis4--;
			}
			if(lap_cnt == 3)
			{
				angle3--;
				angle4--;
				dis3-=2;
//				dis4--;
			}
			if(lap_cnt < 4) 
			{   // 标志位判断
				white_time = 0;
				workstep = 0; // 重置工作步骤到case0
			} 
			else if(lap_cnt >= 4)
			{
				// 停车操作
				Motor_Stop();
				lap_cnt = 0;
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


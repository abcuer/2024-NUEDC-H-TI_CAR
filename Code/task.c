#include "task.h"
#define TimeLimit 11000

#define StraightSpeed 320
#define TurnSpeed 190
#define TrackSpeed 280

uint8_t workstep = 0;
int16_t turn_time = 0;
uint8_t turn_flag = 0;
uint8_t Task4_CNT = 0;



void Task_1(void)
{
	switch(workstep)
	{
		case 0:
			Line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			pid_Init(&angle, POSITION_PID, 8, 0, 35);
			basespeed = 300;
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
			
		case 2:  // 停车
			SoundLight();
			motor_stop();
			delay_ms(100);
			if(Line_flag)
			{	
				Task = 0; 
				first_flag = 0;
				start_flag = 0;
				Line_flag = 0;
				basespeed = 0;
				workstep = 0;
				delay_ms(400); 
			}
			break;
	}
}

void Task_2(void)
{
	switch(workstep)
	{
		case 0: 
			Line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			pid_Init(&angle, POSITION_PID, 8, 0, 35);
			basespeed = 310;
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
		
		case 2: // 寻迹
			SoundLight();
			delay_ms(400);
			basespeed = 290;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			workstep++;
			break;
			
		case 3: // 直行
			SoundLight();
			pid_Init(&angle, POSITION_PID, 8, 0, 35);
		    delay_ms(500);
			basespeed = 320;
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
			
		case 4: // 寻迹
			SoundLight();
			delay_ms(500);
			basespeed = 290;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			workstep++;
			break;
			
		case 5:	
			SoundLight(); 
			motor_stop();
			delay_ms(100);
			if(Line_flag == 0) turn_flag = 1;
			basespeed = 0;
			pid_Init(&angle, POSITION_PID, 7, 0, 2.5);
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit + 200)
				{	
					motor_stop();
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
					Task = 0; 
					first_flag = 0;
					start_flag = 0;
					Line_flag = 0;
					basespeed = 0;
					workstep = 0;
				}
			}
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
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1);
			basespeed = StraightSpeed;
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis1) && (fabsf(carR_dis) <= dis1))
			{
				angle_pid_control(-46);
				distance();
			}
			motor_stop();
			delay_ms(300);
			
			// 回正
			basespeed = TurnSpeed;
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1.5);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			motor_stop();
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			motor_stop();
			delay_ms(100);
			// 回正
			if(Line_flag) turn_flag = 1;
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			basespeed = 0;
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 寻迹
			basespeed = TrackSpeed;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			motor_stop();
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			motor_stop();
			delay_ms(100);
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			// 回正
			if(Line_flag == 0) turn_flag = 1;
			basespeed = 0;
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 转弯
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1);
			basespeed = StraightSpeed;
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis2) && (fabsf(carR_dis) <= dis2))
			{
				angle_pid_control(50);
				distance();
			}
			motor_stop();
			delay_ms(300);
			
			// 回正
			basespeed = TurnSpeed;
			pid_Init(&angle, POSITION_PID, 5.0, 0, 2);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			motor_stop();
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			motor_stop();
			delay_ms(100);
			
			// 回正 
			basespeed = 0;
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			if(Line_flag)  turn_flag = 1;
			while(turn_flag) 
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 寻迹
			basespeed = TrackSpeed;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			motor_stop();
			workstep++;
			break;
			
			
		case 5:  // 停车
			SoundLight(); 
			motor_stop();
			delay_ms(100);
			if(Line_flag == 0) turn_flag = 1;
			basespeed = 0;
			pid_Init(&angle, POSITION_PID, 7, 0, 2.5);
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit + 150)
				{	
					motor_stop();
					carL_dis = 0;
					carR_dis = 0;
					Get_Encoder_countA = 0;
					Get_Encoder_countB = 0;
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
					Task = 0; 
					first_flag = 0;
					start_flag = 0;
					Line_flag = 0;
					basespeed = 0;
					workstep = 0;
				}
			}
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
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1);
			basespeed = StraightSpeed;
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis1) && (fabsf(carR_dis) <= dis1))
			{
				angle_pid_control(-46);
				distance();
			}
			motor_stop();
			delay_ms(300);
			
			// 回正
			basespeed = TurnSpeed;
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1.5);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			motor_stop();
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			motor_stop();
			delay_ms(100);
			// 回正
			if(Line_flag) turn_flag = 1;
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			basespeed = 0;
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 寻迹
			basespeed = TrackSpeed;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			motor_stop();
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			motor_stop();
			delay_ms(100);
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			// 回正
			if(Line_flag == 0) turn_flag = 1;
			basespeed = 0;
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 转弯
			pid_Init(&angle, POSITION_PID, 5.0, 0, 1);
			basespeed = StraightSpeed;
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis2) && (fabsf(carR_dis) <= dis2))
			{
				angle_pid_control(50);
				distance();
			}
			motor_stop();
			delay_ms(300);
			
			// 回正
			basespeed = TurnSpeed;
			pid_Init(&angle, POSITION_PID, 5.0, 0, 2);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			motor_stop();
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			motor_stop();
			delay_ms(100);
			
			// 回正 
			basespeed = 0;
			pid_Init(&angle, POSITION_PID, 7, 0, 3);
			if(Line_flag)  turn_flag = 1;
			while(turn_flag) 
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit)
				{	
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			delay_ms(300);
			
			// 寻迹
			basespeed = TrackSpeed;
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control();
			}
			motor_stop();
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLight(); 
			motor_stop();
			delay_ms(100);
			if(Line_flag == 0) turn_flag = 1;
			basespeed = 0;
			pid_Init(&angle, POSITION_PID, 7, 0, 2.5);
			while(turn_flag)
			{
				angle_pid_control(angle_initial);
				turn_time++;
				if(turn_time > TimeLimit + 150)
				{	
					motor_stop();
					carL_dis = 0;
					carR_dis = 0;
					Get_Encoder_countA = 0;
					Get_Encoder_countB = 0;
					baisetime = 0;
					turn_time = 0;
					turn_flag = 0;
				}
			}
			Task4_CNT++;
			if(Task4_CNT < 4) 
			{   // 标志位判断
				workstep = 1; // 重置工作步骤到case1
				basespeed = StraightSpeed;
			} 
			else if(Task4_CNT >= 4)
			{
				// 停车操作
				motor_stop();
				Task4_CNT = 0;
				basespeed = 0;
				workstep = 0;
				Task = 0; 
				first_flag = 0;
				start_flag = 0;
				Line_flag = 0;
			}
			delay_ms(400);
			break;	
	}
}

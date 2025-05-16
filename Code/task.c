#include "headfile.h"
#define TimeLimit 11900

uint8_t workstep = 0;
int16_t turn_time = 0;
uint8_t turn_flag = 0;
uint8_t Task4_CNT = 0;

float angle1 = -43;  /* 39、40: 直接贴死，但会有bug*/ //Task3
float angle2 = 52;	/*  43 ：直接贴死*/               //Task3

float angle3 = -44;  /* 39、40: 直接贴死，但会有bug*/ //Task4
float angle4 = 50;                                    //Task4

void Task_1(void)
{
	switch(workstep)
	{
		case 0:
			Line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			pid_Init(&angle, POSITION_PID, -8, 0, -0);
			basespeed = 400;
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
			
		case 2:  // 停车
			SoundLight();
			basespeed = 0;
			motor_stop();
			//delay_ms(100);
			if(Line_flag)
			{	
				Task = 0; 
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
			pid_Init(&trackLine, POSITION_PID, 4.8, 0, 0);//4.8,0,1.5
			pid_Init(&angle, POSITION_PID, -8, 0, -0);
			Line_flag = 0;
			basespeed = 400;
			workstep++;
			break;
		
		case 1:  // 直行
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
		
		case 2: // 寻迹
			SoundLight();
			basespeed = 390;
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			workstep++;
			break;
			
		case 3: // 直行
			SoundLight();
			basespeed = 400;
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angle_pid_control(angle_initial);
			}
			workstep++;
			break;
			
		case 4: // 寻迹
			SoundLight();
			basespeed = 390;
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			SoundLight();
			workstep++;
			break;
			
		case 5:	
			basespeed = 0;
			motor_stop();
			delay_ms(100);
			baisetime = 0;
			turn_time = 0;
			turn_flag = 0;
			Task = 0; 
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
			pid_Init(&angle, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				angle_pid_control(angle3);
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
				angle_pid_control(angle3);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(7);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			// 寻迹			}

			basespeed = 390;
			pid_Init(&trackLine, POSITION_PID, 4.8, 0, 0);
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			basespeed = 0;
			turn_flag = 1;
			while(turn_flag)
			{
				angle_pid_control(angle4);
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
				angle_pid_control(angle4);
				distance();
			}
			pid_Init(&angle, POSITION_PID, -7, 0, -0);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(-2.5);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			basespeed = 390;
			pid_Init(&trackLine, POSITION_PID, 4.7, 0, 0);
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLight(); 
			motor_stop();
			delay_ms(100);
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
			pid_Init(&angle, POSITION_PID, -7, 0, -0.1);
			while(turn_flag)
			{
				angle_pid_control(angle3);
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
				angle_pid_control(angle3);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(7);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			// 寻迹		
			basespeed = 390;
			pid_Init(&trackLine, POSITION_PID, 4.8, 0, 0);
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			basespeed = 0;
			turn_flag = 1;
			while(turn_flag)
			{
				angle_pid_control(angle4);
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
				angle_pid_control(angle4);
				distance();
			}
			pid_Init(&angle, POSITION_PID, -7, 0, -0);
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angle_pid_control(-4);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			basespeed = 390;
			pid_Init(&trackLine, POSITION_PID, 4.7, 0, 0);
			while(Line_flag)
			{
				Get_Light_TTL();
				track2_pid_control();
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLight();
			Task4_CNT++;
			Line_flag = 0;
			angle3 = -44;
			angle4 = 50;
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
				motor_stop();
				Task4_CNT = 0;
				basespeed = 0;
				workstep = 0;
				Task = 0; 
				first_flag = 0;
				start_flag = 0;
				delay_ms(100);
			}
			break;	
	}
}


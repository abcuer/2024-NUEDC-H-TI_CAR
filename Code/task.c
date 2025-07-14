#include "headfile.h"
#define TimeLimit 12000

uint8_t workstep = 0;
int16_t turn_time = 0;
uint8_t turn_flag = 0;
uint8_t Task4_CNT = 0;

float angle3 = -50;  /* 39、40: 直接贴死，但会有bug*/ //Task4
float angle4 = 64;                                    //Task4


//void Task_1(void)
//{
//	static float distance_after_stopline2 = 0; // 直行距离计数

//	switch(workstep)
//	{
//		case 0:
//			pid_Init(&trackLine, POSITION_PID, 0.25, 0, 0);
//			pid_Init(&angle, POSITION_PID, -0.35, 0, 0);
//			basespeed = 300;
//			Line_flag = 1;
//			stop_flag = 0;
//			distance_after_stopline2 = 0;
//			workstep++;
//			break;
//		
//		case 1:  // 直行巡线，跑第二圈
//			if(stop_line < 2)
//			{				
//				Get_Light_TTL();
//				trackloop_pid_control(0, basespeed);
//			}
//			else
//			{
//				basespeed = 300;   // 继续直行，准备计距离
//				distance_after_stopline2 = 0;
//				workstep++;  // 进入直行一段距离阶段
//			}
//			break;

//		case 2:  // 第二圈结束后，继续直行一段距离
//			{
//				Get_Light_TTL();
//				trackloop_pid_control(0, basespeed);

//				// 用编码器或里程计测量已经走的距离，累加
//				distance_after_stopline2 += get_distance(); 

//				// 假设想走0.5米后再转弯
//				if(distance_after_stopline2 >= 70.0f) 
//				{
//					basespeed = 0; // 停止前进，准备转弯
//					workstep++;
//				}
//			}
//			break;

//		case 3:  // 转90度进入新的巡线模式
//			angleloop_pid_control(90, 0); // 转90度
//			if (fabs(fabs(angle.now) - 90) < ANGLE_THRESHOLD)  // 角度误差阈值
//			{
//				workstep++;  // 转完角度，进入巡线新阶段
//				basespeed = 300;  // 恢复速度
//			}
//			break;

//		case 4:  // 新巡线模式，等待stop_line == 3
//			if(stop_line < 3)
//			{
//				Get_Light_TTL();
//				trackloop_pid_control(0, basespeed);
//			}
//			else  // stop_line == 3
//			{
//				stop_flag = 1;
//				motor_stop();
//				SoundLight();

//				// 重置任务状态
//				Line_flag = 0;
//				workstep = 0;
//				Task = 0;
//				first_flag = 0;
//				start_flag = 0;
//			}
//			break;
//	}
//}

#define STOP_DELAY_MS 2000    // 停车停留时间，比如2秒
#define ANGLE_THRESHOLD 8.0f  // 角度误差阈值

void Task_1(void)
{
    static float distance_after_stopline2 = 0; // 直行距离计数
    static unsigned long stop_start_time = 0;

	switch(workstep)
	{
		case 0:
			pid_Init(&trackLine, POSITION_PID, 0.25, 0, 0);
			pid_Init(&angle, POSITION_PID, -0.35, 0, 0);
			basespeed = 300;
			Line_flag = 1;
			stop_flag = 0;
			distance_after_stopline2 = 0;
			workstep++;
			break;
		
		case 1:  // 直行巡线，跑第二圈
			if(stop_line < 1)
			{				
				Get_Light_TTL();
				trackloop_pid_control(0, basespeed);
			}
			else
			{
				basespeed = 300;   // 继续直行，准备计距离
				distance_after_stopline2 = 0;
				workstep++;  // 进入直行一段距离阶段
			}
			break;

		case 2:  // 第二圈结束后，继续直行一段距离
			Get_Light_TTL();
			trackloop_pid_control(0, basespeed);
			distance_after_stopline2 += get_distance(); 
			if(distance_after_stopline2 >= 67.0f) // 70cm
			{
				basespeed = 0; // 停止前进，准备转弯
				workstep++;
			}
			break;

		case 3:  // 转90度进入新的巡线模式
			angleloop_pid_control(90, 0); 
			if (fabs(angle.now - 90) < ANGLE_THRESHOLD)  
			{
				workstep++;  
				basespeed = 300;  
			}
			break;

		case 4:  // 新巡线模式，等待stop_line == 2（终点）
			if(stop_line < 2 && stop_flag == 0)
			{
				Get_Light_TTL();
				trackloop_pid_control(0, basespeed);
			}
			else  // 到达终点，停车
			{
				motor_stop();
				stop_flag = 1;
				delay_ms(2000);
//				stop_start_time = millis();  // 记录停车时间
				workstep++;
			}
			break;

		case 5:  // 终点停一会
//			if(millis() - stop_start_time >= STOP_DELAY_MS)
//			{
		//  当前角度为90度
			stop_line = 0;
			stop_flag = 0;
			pid_Init(&trackLine, POSITION_PID, 0.25, 0, 0);
			pid_Init(&angle, POSITION_PID, -0.35, 0, 0);  // 重新初始化角度环
			workstep++;
			//}
			break;

		case 6:
			distance_after_stopline2 = 0;  // 清零！
			angleloop_pid_control(-94, 0); 
			if (fabs(angle.now + 90) < ANGLE_THRESHOLD)
			{
				workstep++;
				basespeed = 300;
			}
			break;

		case 7:  // 转180后继续寻迹，直到回到起点（假设起点stop_line==0）
			if(stop_line < 1)
			{
				Get_Light_TTL();
				trackloop_pid_control(0, basespeed);
				distance_after_stopline2 = 0;
			}
			else
			{
				distance_after_stopline2 += get_distance(); 
				if(distance_after_stopline2 >= 90.0f) // 80cm
				{
					basespeed = 0; // 停止前进，准备转弯
					workstep++;
				}
			}
			break;
		case 8:
			angleloop_pid_control(-179, 0); 
			if (fabs(angle.now + 179) < ANGLE_THRESHOLD)  
			{
				workstep++;  
				basespeed = 300;  
			}
			break;
			
		case 9:  // 最后一次巡线，终点停车
		if(stop_line < 3 && stop_flag == 0)
		{
			Get_Light_TTL();
			trackloop_pid_control(0, basespeed);
		}
		else
		{
			motor_stop();
			basespeed = 0;
			stop_flag = 1;
			SoundLight();

			// 重置状态
			workstep = 0;
			Task = 0;
			first_flag = 0;
			start_flag = 0;
		}
		break;
	}
}


void Task_2(void)
{
	switch(workstep)
	{
		case 0: 
			pid_Init(&angle, POSITION_PID, -0.30, -0, -0);
			pid_Init(&trackLine, POSITION_PID, 4.3, 0, 0);
			Line_flag = 0;
			workstep++;
			break;
		
		case 1:  // 直行
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angleloop_pid_control(angle_initial, 300);
			}
			workstep++;
			break;
		
		case 2: // 寻迹
			SoundLight();
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
			}
			workstep++;
			break;
			
		case 3: // 直行
			SoundLight();
			while(Line_flag == 0)
			{				
				Get_Light_TTL();
				angleloop_pid_control(angle_initial, 300);
			}
			workstep++;
			break;
			
		case 4: // 寻迹
			SoundLight();
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
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
			pid_Init(&angle, POSITION_PID, -0.34, -0, -0);
			pid_Init(&trackLine, POSITION_PID, 4.3, 0, 0);
			Line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			turn_flag = 1;
			while(turn_flag)
			{
				angleloop_pid_control(angle3, 300);
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
			while((fabsf(carL_dis) <= dis3) && (fabsf(carR_dis) <= dis3))
			{
				angleloop_pid_control(angle3, 300);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angleloop_pid_control(10, 300);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			// 寻迹			
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			turn_flag = 1;
			while(turn_flag)
			{
				angleloop_pid_control(angle4, 300);
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
			while((fabsf(carL_dis) <= dis4) && (fabsf(carR_dis) <= dis4))
			{
				angleloop_pid_control(angle4, 300);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angleloop_pid_control(-2.5, 300);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
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
			pid_Init(&angle, POSITION_PID, -0.34, -0, -0);
			pid_Init(&trackLine, POSITION_PID, 4.3, 0, 0);
			Line_flag = 0;
			workstep++;
			break;
		
		case 1: // 转弯直行
			// 转弯
			basespeed = 0;
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis3) && (fabsf(carR_dis) <= dis3))
			{
				angleloop_pid_control(angle3, 300);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angleloop_pid_control(10, 300);
			}
			workstep++;
			break;
			
		case 2:  // 先回正再寻迹
			SoundLight();
			// 寻迹			
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
			}
			workstep ++;
			break;
			
		case 3:  // 先回正再转弯直行
			SoundLight();
			carL_dis = 0;
			carR_dis = 0;
			Get_Encoder_countA = 0;
			Get_Encoder_countB = 0;
			while((fabsf(carL_dis) <= dis4) && (fabsf(carR_dis) <= dis4))
			{
				angleloop_pid_control(angle4, 300);
				distance();
			}
			while(Line_flag == 0)
			{
				Get_Light_TTL();
				angleloop_pid_control(-5, 300);
			}
			workstep++;
			break;
		
		case 4:  // 先回正再寻迹
			SoundLight();
			while(Line_flag)
			{
				Get_Light_TTL();
				track_pid_control(0, 300);
			}
			workstep++;
			break;
			
		case 5:  // 停车
			SoundLight();
			Task4_CNT++;
			Line_flag = 0;
//			angle3 = -44;
//			angle4 = 50;
//			dis3 = 995;
//			dis4 = 998;
//			if(Task4_CNT == 1)
//			{
//				dis3 = 992;
////				angle3++;
//			}
//			if(Task4_CNT == 2)
//			{
//				angle3--;
////				angle4--;
//				dis3 = 994;
//				dis4--;
//			}
//			if(Task4_CNT == 3)
//			{
//				angle3--;
//				angle4--;
//				dis3-=2;
////				dis4--;
//			}
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


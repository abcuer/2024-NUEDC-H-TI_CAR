#include "headfile.h"

#define TimeLimit 11900

// --- 全局变量 ---
uint8_t workstep = 0;   // 工作步骤
float basespeed = 0;    // 小车行驶速度
int16_t turn_time = 0;  // 拐角转弯的时间
uint8_t turn_flag = 0;  // 是否启动拐角转弯
uint8_t lap_cnt = 0;    // 任务4记录圈数

// --- 任务3/4 核心参数 ---
float angle3 = -44;     //
float angle4 = 52;      //
float dis3 = 1042;      //
float dis4 = 996;       //

// --- 内部工具函数 (优化核心) ---

/**
 * @brief 统一重置任务状态，清理所有标志位
 */
static void Reset_Task_System(void)
{
    Motor_Stop();
    basespeed = 0;
    workstep = 0;
    turn_flag = 0;
    turn_time = 0;
    white_time = 0;
	line_flag = 0;
    task_num = 0; 
    first_flag = 0;
    start_flag = 0;
    carL_dis = 0;
    carR_dis = 0;
    encoder_left_count = 0;
    encoder_right_count = 0;
    delay_ms(100);
}	

/**
 * @brief 动作：直行直到触发黑线 (用于 A-B 或 C-D)
 */
static void Action_Drive_To_Line(float speed, float target_angle) 
	{
		basespeed = speed;
		while(line_flag == 0) 
		{
			// 检测黑线
			Gray_ProcessLine();
			AnglePidCtrl(target_angle);
		}
		SoundLightRun(); // 到达节点提示
}

/**
 * @brief 动作：寻迹直到离开黑线 (用于圆弧段)
 */
static void Action_Track_To_White(float speed, float kp)
{
    basespeed = speed;
    PID_Update(&track_pid, POSITION_PID, kp, 0, 0);
    while(line_flag) 
	{
        Gray_ProcessLine();
        TrackPidCtrl();
    }
    SoundLightRun(); // 到达节点提示
}

/**
 * @brief 动作：转向并行驶一段固定距离 (用于 Task 3/4 的斜穿)
 */
static void Action_Turn_And_Distance(float angle, float distance) 
{
    // 1. 原地转向阶段
    basespeed = 0;
    turn_flag = 1;
    turn_time = 0;
    PID_Update(&angle_pid, POSITION_PID, -7, 0, -0.1);
    while(turn_flag)
	{
        AnglePidCtrl(angle);
        if(++turn_time > TimeLimit) turn_flag = 0; // 超时退出
    }
    // 2. 定距行驶阶段
    carL_dis = 0; carR_dis = 0;
    encoder_left_count = 0; encoder_right_count = 0;
    basespeed = 480;
    while((fabsf(carL_dis) <= distance) && (fabsf(carR_dis) <= distance))
	{
        AnglePidCtrl(angle);
        Car_GetDistance();
    }
}

// --- 任务实现 ---
void FirstTask(void) 
{
    switch(workstep) 
	{
        case 0: line_flag = 0; workstep++; break;
        case 1: 
            PID_Update(&angle_pid, POSITION_PID, -8, 0, 0);
            Action_Drive_To_Line(400, 0); // 直行到B
            workstep++;
            break;
        case 2: Reset_Task_System(); break;
    }
}

void SecondTask(void) 
{
    switch(workstep) 
	{
        case 0: line_flag = 0; workstep++; break;
        case 1: // A -> B 直行
            PID_Update(&angle_pid, POSITION_PID, -8, 0, 0);
            Action_Drive_To_Line(400, 0); 
            workstep++; break;
        case 2: // B -> C 寻迹
            Action_Track_To_White(390, 4.8); 
            workstep++; break;
        case 3: // C -> D 直行
            Action_Drive_To_Line(400, 0); 
            workstep++; break;
        case 4: // D -> A 寻迹
            Action_Track_To_White(390, 4.8); 
            workstep++; break;
        case 5: Reset_Task_System(); break;
    }
}

/**
 * @brief Task 3 和 4 的通用逻辑执行器
 */
static void Execute_Diagonal_Logic(uint8_t is_multi_lap) 
{
    switch(workstep) 
	{
        case 0: line_flag = 0; workstep++; break;
        case 1: // A -> C (转向+定距直行)
            Action_Turn_And_Distance(angle3, dis3);
            Action_Drive_To_Line(480, 7);
            workstep++; break;
        case 2: // C -> B (寻迹)
            Action_Track_To_White(390, 4.8);
            workstep++; break;
        case 3: // B -> D (转向+定距直行)
            Action_Turn_And_Distance(angle4, dis4);
            Action_Drive_To_Line(480, -1);
            workstep++; break;
        case 4: // D -> A (寻迹)
            Action_Track_To_White(390, 4.7);
            workstep++; break;
        case 5:
            if (is_multi_lap) 
			{
                lap_cnt++;
                // Task 4 动态补偿逻辑
                angle3 = -44; angle4 = 51; dis3 = 995; dis4 = 998;
                if(lap_cnt == 1) dis3 = 992;
                if(lap_cnt == 2) { angle3--; dis3 = 994; dis4--; }
                if(lap_cnt == 3) { angle3--; angle4--; dis3 -= 2; }

                if(lap_cnt < 4) { workstep = 0; white_time = 0; } 
                else { lap_cnt = 0; Reset_Task_System(); }
            } 
			else 
			{
                Reset_Task_System();
            }
            break;
    }
}

void ThirdTask(void) 
{
	Execute_Diagonal_Logic(0); 
}  // 跑一圈

void FourthTask(void) 
{
	Execute_Diagonal_Logic(1); 
} // 跑四圈

#include "pid.h"

uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
                 // Device header
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

void pid_clear(pid_t *pid)
{
    pid->error[0] = 0;
    pid->error[1] = 0;
    pid->error[2] = 0;
    pid->pout = 0;
    pid->iout = 0;
    pid->dout = 0;
    pid->out = 0;
    pid->now = 0;
    pid->target = 0;
}


void pid_cal(pid_t *pid)
{
	// ���㵱ǰƫ��
	pid->error[0] = pid->target - pid->now;

	// �������
	if(pid->pid_mode == DELTA_PID)  // ����ʽ
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // λ��ʽ
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// ��¼ǰ����ƫ��
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void pidout_limit(pid_t *pid, float duty)
{
	if(pid->out >= duty)	pid->out = duty;
	if(pid->out <= -duty) pid->out = -duty;
}


float PID_Increase(pid_t *pid, float Now, float Tar)
{
    uint32_t Increase = 0;

    // 计算当前误差
    pid->error[0] = Tar - Now;

    // 增量式 PID 计算公式：
    // Δu = P * (e(k) - e(k-1)) + I * e(k) + D * (e(k) - 2e(k-1) + e(k-2))
    Increase = (pid->p * (pid->error[0] - pid->error[1])
                        + pid->i * pid->error[0]
                        + pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]));

    // 更新误差历史，为下一次计算做准备
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];

    return Increase;
}

float VelcityA_Ki = 10.2, VelcityA_Kp = 0.02;
float VelcityB_Ki = 9.6 , VelcityB_Kp = 0.03;
/***************************************************************************
函数功能：电机的PID闭环控制
入口参数：左右电机的编码器值
返回值  ：电机的PWM
***************************************************************************/

int Velocity_A(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //定义相关变量
	static int ControlVelocityA, Last_biasA; //静态变量，函数调用结束后其值依然存在
	
	Bias=TargetVelocity-CurrentVelocity; 
	ControlVelocityA+=VelcityA_Ki*(Bias-Last_biasA)+VelcityA_Kp*Bias;  //增量式PI控制器														
	Last_biasA=Bias;	
	if(ControlVelocityA>340) ControlVelocityA=340;
	else if(ControlVelocityA<-340) ControlVelocityA=-340;
	return ControlVelocityA; //返回速度控制值
}

/***************************************************************************
函数功能：电机的PID闭环控制
入口参数：左右电机的编码器值
返回值  ：电机的PWM
***************************************************************************/
int Velocity_B(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //定义相关变量
	static int ControlVelocityB, Last_biasB; //静态变量，函数调用结束后其值依然存在
	
	Bias=TargetVelocity-CurrentVelocity; 
	ControlVelocityB += VelcityB_Ki*(Bias-Last_biasB) + VelcityB_Kp*Bias;  //增量式PI控制器														
	Last_biasB=Bias;	
	if(ControlVelocityB>340) ControlVelocityB=340;
	else if(ControlVelocityB<-340) ControlVelocityB=-340;
	return ControlVelocityB; //返回速度控制值
}

void speed2_pid_control(int speed_tar)
{
	speed_cal(0.5);
	float PWMA = Velocity_A(speed_tar, speedA);
	float PWMB = Velocity_B(speed_tar, speedB);
	if(PWMA > 0) motor_left_dir = 1; 	else motor_left_dir = 0;
	if(PWMB > 0) motor_right_dir = 1;	else motor_right_dir = 0;
	Motor_left_Control(fabs(PWMA));
	Motor_right_Control(fabs(PWMB));
}

void speed_pid_control(int speed_tar, int base)
{
	speed_cal(0.5);
	if (abs(speed_tar) < 5) speed_tar = 0;
	float PWMA = base - Velocity_A(speed_tar, speedA);
	float PWMB = base + Velocity_B(speed_tar, speedB);
	if(PWMA >= 0) motor_left_dir = 1; 	else motor_left_dir = 0;
	if(PWMB >= 0) motor_right_dir = 1;	else motor_right_dir = 0;
	Motor_left_Control(fabs(PWMA));
	Motor_right_Control(fabs(PWMB));
}

// 角度环
pid_t angle;
int ang = 0;

void angle_correction(void)
{
	if(Task == 2)
	{
		if( ang > 120) ang -= 180;
		else if( ang < -120) ang += 180;
	}
	else if(Task == 3 || Task == 4)
	{
		if(workstep == 1 || workstep == 2)
		{
			if( ang > 125) ang -= 180;
			else if( ang < -125) ang += 180;
		}
		if(workstep == 3 || workstep == 4)
		{
			if( ang > 70) ang -= 180;
			else if( ang < -70) ang += 180;
		}
	}
}

int angle_pid_control(float tar)
{
	angle.target = tar;
	ang = Yaw;
	angle_correction();
	angle.now = ang; 
	pid_cal(&angle);
	pidout_limit(&angle, 500);
	return angle.out;
}

//*  串级角度环  */
void angleloop_pid_control(float angle_tar, int base)
{
	int speed_tar = angle_pid_control(angle_tar);  // 74°实际90°160°实际 180°
	speed_pid_control(speed_tar, base);
}

// 寻迹环
pid_t trackLine;

void track_pid_control(float targetValue, float basespeed)
{
	float currentValue = (L4 * (-4) + L3 * (-3) + L2 * (-2) + L1 * (-1) + R1 * 1 + R2 * 2 + R3 * 3 + R4 * 4) / (R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4);
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	Motor_left_Control(basespeed - trackLine.out);
	Motor_right_Control(basespeed + trackLine.out);
}

int track2_pid_control(float targetValue)
{
	// 计算误差
	float currentValue = (L4 * 23 + L3 * 22 + L2 * 21 + L1 * 20 + R1 * (-20) + R2 * (-21) + R3 * (-22) + R4 * (-23)) / (R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4);
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	return trackLine.out;
}

/*  串级寻迹环  */
/* track_tar一般为0 */
void trackloop_pid_control(float track_tar, int base)
{
	int speed_tar = track2_pid_control(track_tar);
	speed_pid_control(speed_tar, base);
}


//float dist_pid_control(float dist_tar)
//{
//	float pulse_tar = dist_tar / Wheel_dist;
//	float puise = (fabs(Get_Encoder_countB) + fabs(Get_Encoder_countA)) / 2.0;
//	dist.now = puise;
//	dist.target = pulse_tar;
//	pid_cal(&dist);
//	return dist.out;
////	if(Increase<2)
////	{
////		motor_stop();
////	} 
//}	
pid_t dist;

// 直径65mm  //一圈脉冲数 730 
// 定义减速比，表示电机轴转 28 圈，轮子转 1 圈
#define MOTOR_REDUCTION_RATIO 10.0f

// 编码器每转输出的脉冲数（通常是电机轴上的编码器）
#define ENCODER_RESOLUTION 730.0f

// 轮子直径（单位：米）
#define WHEEL_DIAMETER 0.065f

// 轮子周长 = π × 直径
#define WHEEL_CIRCUMFERENCE (PI * WHEEL_DIAMETER)

// 单个编码器脉冲对应轮子在地面上的位移（单位：米）
// 注意：这里是**轮子轴**对应的脉冲距离，还没乘减速比
#define WHEEL_DIST (WHEEL_CIRCUMFERENCE / ENCODER_RESOLUTION) // 0.0002797

void dist2_pid_control(float dist_tar_cm)  // 以“厘米”为单位
{
    float pulse_tar = (dist_tar_cm / 100.0f) / WHEEL_DIST * MOTOR_REDUCTION_RATIO;  // cm -> m，再求目标脉冲
    float puise = (abs(Get_Encoder_countB) + abs(Get_Encoder_countA)) / 2.0;

    dist.now = puise;
    dist.target = pulse_tar;

    pid_cal(&dist);

    // 使用 PID 输出驱动电机
    Motor_left_Control(dist.out);
    Motor_right_Control(dist.out);

    // 误差很小就停车
    if(fabs(dist.target - dist.now) < 2.0f)  // 脉冲误差阈值
    {
        motor_stop();
    }
}

/**
 * @brief 位移PID控制函数，让小车移动指定距离
 * @param dist_tar_cm 目标位移（单位：厘米）
 * @return PID输出值（通常用于控制电机PWM）
 */
 
float dist_pid_control(float dist_tar_cm)
{
    // 将目标距离从 cm 转换为 m，并计算目标对应的脉冲数（考虑减速比）
    float pulse_tar = (dist_tar_cm / 100.0f) / WHEEL_DIST;
    // 获取当前小车两轮的平均编码器值（即当前位移对应的脉冲数）
    float puise = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    dist.now = puise;
    dist.target = pulse_tar;
    pid_cal(&dist);
	if(fabs(dist.out) < 5.0f) dist.out = 0;  // 避免微抖动
    return dist.out;
}

void distloop_pid_control(float dist_tar, int base)
{
	int speed_tar = dist_pid_control(dist_tar);
	speed_pid_control(speed_tar, base);
    if(fabs(dist.target - dist.now) < 50.0f)  // 脉冲误差阈值
    {
       motor_stop(); // 连续5次满足条件才停
    }
}
/*轮子一圈脉冲：编码器线序*倍频*减速比
	13*2*28 = 728
	每脉冲度数 = 360 ➗ 电机旋转一圈的编码器脉冲数
*/
/** 使用编码器进行pid转向 **/
pid_t encoder_to_ang;
float One_Wheel_angle = 360.0f / 728.0f;

void encoder_to_angle(float angle_tar)
{
    encoder_to_ang.target = angle_tar / One_Wheel_angle;
    encoder_to_ang.now = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    
    float error = encoder_to_ang.target - encoder_to_ang.now;

    // 判断是否到达目标角度
    if (fabsf(error) < 2.0f) // 允许误差小于 2 脉冲（视精度而定）
    {
        Motor_left_Control(0);   // 停止电机
        Motor_right_Control(0);
        return; // 不再执行 PID 控制
    }

    pid_cal(&encoder_to_ang);
    pidout_limit(&encoder_to_ang, 3000);
    Motor_left_Control( - encoder_to_ang.out);
    Motor_right_Control( + encoder_to_ang.out);
}



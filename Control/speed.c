#include "headfile.h"

float speedA = 0;
float speedB = 0;

void speed_cal(float filter_alpha)
{
    static int32_t last_countA = 0;
    static int32_t last_countB = 0;
    int32_t nowA = Get_Encoder_countA;
    int32_t nowB = Get_Encoder_countB;
    int32_t deltaA = nowA - last_countA;
    int32_t deltaB = nowB - last_countB;
    last_countA = nowA;
    last_countB = nowB;
    float raw_speedA = ((float)deltaA / ENCODER_RESOLUTION) * (PI * 0.065f) / 0.008f;
    float raw_speedB = ((float)deltaB / ENCODER_RESOLUTION) * (PI * 0.065f) / 0.008f;
    // 静态变量保存上一次的速度
    static float last_speedA = 0;
    static float last_speedB = 0;
    speedA = filter_alpha * raw_speedA + (1 - filter_alpha) * last_speedA;
    speedB = filter_alpha * raw_speedB + (1 - filter_alpha) * last_speedB;
    // 更新旧值
    last_speedA = speedA;
    last_speedB = speedB;
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

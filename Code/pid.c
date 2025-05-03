#include "pid.h"

uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

// 速度环
pid_t motorA;
pid_t motorB;
float last_encoderA_cnt = 0;
float last_encoderB_cnt = 0;
float encoderA_cnt = 0;
float encoderB_cnt = 0;

// 寻迹环
pid_t trackLine;
int16_t targetValue = 0; // 目标值设为中线位置
int8_t currentValue = 0; // 当前值初始化

// 角度环
pid_t angle;
int ang = 0;


void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
                 // Device header
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
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

void track_pid_control(void)
{
	// 计算误差
//	currentValue = (L4 * 26 + L3 * 22 + L2 * 20 + L1 * 18 + R1 * (-18) + R2 * (-20) + R3 * (-22) + R4 * (-26)) / (R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4);
	currentValue = (L4 * 26 + L3 * 24 + L2 * 23 + L1 * 22 + R1 * (-22) + R2 * (-23) + R3 * (-24) + R4 * (-26)) / (R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4);
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	Motor_left_Control(basespeed - trackLine.out);
	Motor_right_Control(basespeed + trackLine.out);
}

void angle_pid_control(float tar)
{
	
	angle.target = tar;
	ang = Yaw;
	angle_correction();
	angle.now = ang; 
	pid_cal(&angle);
	pidout_limit(&angle, 500);
	Motor_left_Control(basespeed - angle.out);
	Motor_right_Control(basespeed + angle.out);
}

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

void speed_pid_control(void)
{
//	encoderA_cnt = Get_Encoder_countA;//origin--2.955 28 jiansubi
//	encoderB_cnt = Get_Encoder_countB;//origin--2.955 28 jiansubi
//	encoderA_cnt = encoderA_cnt * 0.5 + last_encoderA_cnt * 0.5;
//	encoderB_cnt = encoderB_cnt * 0.5 + last_encoderB_cnt * 0.5;
//	last_encoderA_cnt = encoderA_cnt;
//	last_encoderB_cnt = encoderB_cnt;
//	Get_Encoder_countA = 0;
//	Get_Encoder_countB = 0;
//	if(motor_left_dir) motorA.now = encoderA_cnt;				else motorA.now = -encoderA_cnt;
//	if(motor_right_dir) motorB.now = encoderB_cnt;				else motorB.now = -encoderB_cnt;
//	// 3.??PID???????
//	pid_cal(&motorA);
//	pid_cal(&motorB);
//	// ??????
//	pidout_limit(&motorA, 2000);
//	pidout_limit(&motorB, 2000);	
	Motor_left_Control(motorA.out);
	Motor_right_Control(motorB.out);
}

//void motor_target_set(int tarA, int tarB)
//{
//	if(tarA >= 0) 
//	{
//		motor_left_dir = 0;
//		motorA.target = tarA;
//	}
//	else
//	{
//		motor_left_dir = 1;
//		motorA.target = -tarA;
//	}
//	if(tarB >= 0) 
//	{
//		motor_right_dir = 0;
//		motorB.target = tarB;
//	}
//	else
//	{
//		motor_right_dir = 1;
//		motorB.target = -tarB;
//	}
//}

//void track2_pid_control(void)
//{
//	float err = 0,leftSpeed = 0, rightSpeed = 0;
//	static float trackout,lastErr;
//	
//	if(R4 == 1) err -= 4.1;
//	else if(R3 == 1) err -= 3.2;
//	else if(R2 == 1) err -= 2.3;
//	else if(R1 == 1) err -= 1;
//	else if(L1 == 1) err += 1;
//	else if(L2 == 1) err += 2.3;
//	else if(L3 == 1) err += 3.2;
//	else if(L4 == 1) err += 4.1;
//	
//	trackout = track_kp * err + track_kd * (err - lastErr);
//    lastErr = err;
//	
//	leftSpeed = basespeed - trackout;
//	rightSpeed = basespeed + trackout;
//	
//	if (leftSpeed < 0) leftSpeed = 0;
//    if (leftSpeed > 1000) leftSpeed = 1000;
//    if (rightSpeed < 0) rightSpeed = 0;
//    if (rightSpeed > 1000) rightSpeed = 1000;
//	
//	Motor_left_Control(leftSpeed);
//	Motor_right_Control(rightSpeed);
//}
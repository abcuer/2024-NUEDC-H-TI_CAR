#include "pid.h"

uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

// é€Ÿåº¦çŽ¯
pid_t motorA;
pid_t motorB;
float last_encoderA_cnt = 0;
float last_encoderB_cnt = 0;
float encoderA_cnt = 0;
float encoderB_cnt = 0;

// å¯»è¿¹çŽ¯
pid_t trackLine;
int16_t targetValue = 0; // ç›®æ ‡å€¼è®¾ä¸ºä¸­çº¿ä½ç½®
int8_t currentValue = 0; // å½“å‰å€¼åˆå§‹åŒ–

// è§’åº¦çŽ¯
pid_t angle;



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
	// ¼ÆËãµ±Ç°Æ«²î
	pid->error[0] = pid->target - pid->now;

	// ¼ÆËãÊä³ö
	if(pid->pid_mode == DELTA_PID)  // ÔöÁ¿Ê½
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // Î»ÖÃÊ½
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// ¼ÇÂ¼Ç°Á½´ÎÆ«²î
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void pidout_limit(pid_t *pid, float duty)
{
	if(pid->out >= duty)	pid->out = duty;
	if(pid->out <= -duty) pid->out = -duty;
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

void motor_target_set(int tarA, int tarB)
{
	if(tarA >= 0) 
	{
		motor_left_dir = 0;
		motorA.target = tarA;
	}
	else
	{
		motor_left_dir = 1;
		motorA.target = -tarA;
	}
	if(tarB >= 0) 
	{
		motor_right_dir = 0;
		motorB.target = tarB;
	}
	else
	{
		motor_right_dir = 1;
		motorB.target = -tarB;
	}
}

void track_pid_control(void)
{
//	if(R3 | R2 | R1) targetValue = 5;
//	else if(L1 | L2 | L3) targetValue = -5;
	currentValue = (R3 * 26 + R2 * 23 + R1 * 21 + M * targetValue + L1 * -21 + L2 * -23  + L3 * -26) / (R1 + R2 + R3 + M + L1 + L2 + L3);
	// è®¡ç®—è¯¯å·®
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// ç”µæœºè¾“å‡ºé™å¹…
	pidout_limit(&trackLine, 800);
	Motor_left_Control(basespeed - trackLine.out);
	Motor_right_Control(basespeed + trackLine.out);
}

void angle_pid_control(float tar)
{
	
	angle.target = tar;
	int ang = Yaw;
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
	angle.now = ang; 
	pid_cal(&angle);
	pidout_limit(&angle, 400);
	Motor_left_Control(basespeed - angle.out);
	Motor_right_Control(basespeed + angle.out);
}
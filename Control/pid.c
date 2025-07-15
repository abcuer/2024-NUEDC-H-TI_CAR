#include "pid.h"

uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
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
	pid->error[0] = pid->target - pid->now;

	if(pid->pid_mode == DELTA_PID)  
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void pidout_limit(pid_t *pid, float duty)
{
	if(pid->out >= duty)	pid->out = duty;
	if(pid->out <= -duty) pid->out = -duty;
}


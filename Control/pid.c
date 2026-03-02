#include "pid.h"

void PID_Update(PID_Struct *pid, uint8_t mode, float p, float i, float d)
{
    // Device header
	pid->mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

void PID_Calculate(PID_Struct *pid)
{
	pid->error[0] = pid->target - pid->now;

	if(pid->mode == DELTA_PID)  
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->mode == POSITION_PID)  
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void PID_OutPutLimit(PID_Struct *pid, float duty)
{
	if(pid->out >= duty)	pid->out = duty;
	if(pid->out <= -duty) 	pid->out = -duty;
}




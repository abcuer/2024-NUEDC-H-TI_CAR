#include "speed.h"
#include "motor.h"

// 速度环
PID_Struct motor_left_pid;
PID_Struct motor_right_pid;

void SpeedPidCtrl(void)
{
	Motor_LeftCtrl(motor_left_pid.out);
	Motor_RightCtrl(motor_right_pid.out);
}



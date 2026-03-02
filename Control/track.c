#include "track.h"
#include "gray.h"
#include "pid.h"

// 寻迹环
PID_Struct track_pid;

void TrackPidCtrl(void)
{
	// 计算误差
	float sum = 0.0f;
	sum = gray.left[3] + gray.left[2] + gray.left[1] + gray.left[0] + gray.right[0] + gray.right[1] + gray.right[2] + gray.right[3] + 0.0f;
	float current = (gray.left[3] * 24 + gray.left[2] * 22 + gray.left[1] * 21 + gray.left[0] * 20 + gray.right[0]  * (-20) + gray.right[1] * (-21) + gray.right[2] * (-22) + gray.right[3] * (-24)) / sum;
	track_pid.now = current;
	track_pid.target = 0; // 寻迹中线
	PID_Calculate(&track_pid);
	// 电机输出限幅
	PID_OutPutLimit(&track_pid, 800);
	Motor_LeftCtrl(basespeed - track_pid.out);
	Motor_RightCtrl(basespeed + track_pid.out);
}


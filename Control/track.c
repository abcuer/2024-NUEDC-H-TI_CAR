#include "track.h"
#include "gray.h"
#include "pid.h"
#include "task.h"
#include "motor.h"

Gray_Weight_s gray_weight ={
	.left = {20, 21, 22, 24},
	.right = {-20, -21, -22, -24}
};
// 寻迹环
PID_Struct track_pid;

void TrackPidCtrl(void)
{
    float sum = 0.0f;
    float weighted_sum = 0.0f;
	
    for (int i = 0; i < 4; i++)
    {
        sum += (float)(gray.left[i] + gray.right[i]);
        weighted_sum += (float)(gray.left[i] * gray_weight.left[i]);
        weighted_sum += (float)(gray.right[i] * gray_weight.right[i]);
    }
	// 防止除零出错
    if (sum > 0.001f)
        track_pid.now = weighted_sum / sum;
	// 寻迹目标：中心线 (误差为0)
    track_pid.target = 0; 
    PID_Calculate(&track_pid);
    PID_OutPutLimit(&track_pid, 800);
    Motor_LeftCtrl(basespeed - track_pid.out);
    Motor_RightCtrl(basespeed + track_pid.out);
}


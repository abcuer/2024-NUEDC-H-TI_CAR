#include "angle.h"
#include "headfile.h"
// 角度环
PID_Struct angle_pid;

static float Yaw_Normalize(float yaw)
{
    switch (task_num)
    {
        case 2:
            if (yaw > 120.0f)       yaw -= 180.0f;
            else if (yaw < -120.0f) yaw += 180.0f;
            break;

        case 3:
        case 4:
            if (workstep == 1 || workstep == 2)
            {
                if (yaw > 125.0f)       yaw -= 180.0f;
                else if (yaw < -125.0f) yaw += 180.0f;
            }
            else if (workstep == 3 || workstep == 4)
            {
                if (yaw > 70.0f)        yaw -= 180.0f;
                else if (yaw < -70.0f)  yaw += 180.0f;
            }
            break;

        default:
            break;
    }
    return yaw;
}

void AnglePidCtrl(float tar)
{
	angle_pid.target = tar;
	angle_pid.now = Yaw_Normalize(jy901s.yaw - ang_offset); 
	PID_Calculate(&angle_pid);
	PID_OutPutLimit(&angle_pid, 500);
	Motor_LeftCtrl(basespeed - angle_pid.out);
	Motor_RightCtrl(basespeed + angle_pid.out);
}

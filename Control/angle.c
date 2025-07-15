#include "speed.h"
#include "pid.h"

// �ǶȻ�
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

//*  �����ǶȻ�  */
void angleloop_pid_control(float angle_tar, int base)
{
	int speed_tar = angle_pid_control(angle_tar);  // 74��ʵ��90��160��ʵ�� 180��
	speed_pid_control(speed_tar, base);
}

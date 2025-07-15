#include "headfile.h"

// Ѱ����
pid_t trackLine;

void track_pid_control(float targetValue, float basespeed)
{ 	
	float sum = R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4;
	if (sum < 0.001f) sum = 1.0f; // ��������Ĭ��ֵ����ֹ����
	float currentValue = (L4 * 1.0 + L3 * 0.75 + L2 * 0.5 + L1 * 0.25 + R1 * (-0.25) + R2 * (-0.5) + R3 * (-0.75) + R4 * (-1.0)) / sum;
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// �������޷�
	pidout_limit(&trackLine, 800);
	Motor_left_Control(basespeed - trackLine.out);
	Motor_right_Control(basespeed + trackLine.out);
}

int track2_pid_control(float targetValue)
{
	float sum = R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4;
	if (sum < 0.001f) sum = 1.0f; // ��������Ĭ��ֵ����ֹ����
	float currentValue = (L4 * 1.0 + L3 * 0.75 + L2 * 0.5 + L1 * 0.25 + R1 * (-0.25) + R2 * (-0.5) + R3 * (-0.75) + R4 * (-1.0)) / sum;
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// �������޷�
	pidout_limit(&trackLine, 800);
	return trackLine.out;
}

/*  ����Ѱ����  */
/* track_tarһ��Ϊ0 */
void trackloop_pid_control(float track_tar, int base)
{
	int speed_tar = track2_pid_control(track_tar);
	speed_pid_control(speed_tar, base);
}

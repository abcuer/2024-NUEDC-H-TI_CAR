#include "headfile.h"
#include "distance.h"

float carL_dis = 0;
float carR_dis = 0;


/*** ֱ�ӻ�ȡ�ܾ���
***/
void get_distance1(void)
{
	carR_dis = WHEEL_DIST*1000.0f * -Get_Encoder_countB;
	carL_dis = WHEEL_DIST*1000.0f * Get_Encoder_countA;
}

void clear_distance1(void)
{
	carL_dis = 0;
	carR_dis = 0;
	Get_Encoder_countA = 0;
	Get_Encoder_countB = 0;
}

static int lastCountA = 0;
static int lastCountB = 0;

/*** �����Ի�ȡ����
	���ڶ�ʱ���ж���: �ɼ���10ms��С����ʻ����
***/

// ������ 10ms ���ڶ�ʱ����
/*		void Timer_ISR(void)
		{
			distance2 += get_distance();
		}
*/
float get_distance2(void)
{
    int currentCountA = Get_Encoder_countA;
    int currentCountB = Get_Encoder_countB;

    int deltaA = abs(currentCountA - lastCountA);
    int deltaB = abs(currentCountB - lastCountB);

    lastCountA = currentCountA;
    lastCountB = currentCountB;

    float deltaDis_mm = WHEEL_DIST*1000.0f * ((float)deltaA + (float)deltaB) / 2.0f;

    return deltaDis_mm / 10.0f; // ���ص�λ����
}

//float dist_pid_control(float dist_tar)
//{
//	float pulse_tar = dist_tar / Wheel_dist;
//	float puise = (fabs(Get_Encoder_countB) + fabs(Get_Encoder_countA)) / 2.0;
//	dist.now = puise;
//	dist.target = pulse_tar;
//	pid_cal(&dist);
//	return dist.out;
////	if(Increase<2)
////	{
////		motor_stop();
////	} 
//}	
pid_t dist;

	
void dist2_pid_control(float dist_tar_cm)  // �ԡ����ס�Ϊ��λ
{
	//Ŀ������ = Ŀ����ʻ���� �� ÿ�������Ӧ������ǰ������
    float pulse_tar = dist_tar_cm / (100.0f * WHEEL_DIST);
    float puise = (abs(Get_Encoder_countB) + abs(Get_Encoder_countA)) / 2.0;
    dist.now = puise;
    dist.target = pulse_tar;
    pid_cal(&dist);
    Motor_left_Control(dist.out);
    Motor_right_Control(dist.out);
    // ����С��ͣ��
    if(fabs(dist.target - dist.now) < 2.0f)  // ���������ֵ
    {
        motor_stop();
    }
}

/**
 * @brief λ��PID���ƺ�������С���ƶ�ָ������
 * @param dist_tar_cm Ŀ��λ�ƣ���λ�����ף�
 * @return PID���ֵ��ͨ�����ڿ��Ƶ��PWM��
 */
 
float dist_pid_control(float dist_tar_cm)
{
    // ��Ŀ������ cm ת��Ϊ m��������Ŀ���Ӧ�������������Ǽ��ٱȣ�
    float pulse_tar = (dist_tar_cm / 100.0f) / WHEEL_DIST;
    // ��ȡ��ǰС�����ֵ�ƽ��������ֵ������ǰλ�ƶ�Ӧ����������
    float puise = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    dist.now = puise;
    dist.target = pulse_tar;
    pid_cal(&dist);
	if(fabs(dist.out) < 5.0f) dist.out = 0;  // ����΢����
    return dist.out;
}

void distloop_pid_control(float dist_tar, int base)
{
	int speed_tar = dist_pid_control(dist_tar);
	speed_pid_control(speed_tar, base);
    if(fabs(dist.target - dist.now) < 50.0f)  // ���������ֵ
    {
       motor_stop(); // ����5������������ͣ
    }
}
/*  ����һȦ���壺����������*��Ƶ*���ٱ�
	13*2*28 = 728
	ÿ������� = 360 / �����תһȦ�ı�����������
*/
/** ʹ�ñ���������pidת�� **/
pid_t encoder_to_ang;
float One_Wheel_angle = 360.0f / 728.0f;

void encoder_to_angle(float angle_tar)
{
    encoder_to_ang.target = angle_tar / One_Wheel_angle;
    encoder_to_ang.now = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    
    float error = encoder_to_ang.target - encoder_to_ang.now;

    // �ж��Ƿ񵽴�Ŀ��Ƕ�
    if (fabsf(error) < 2.0f) // �������С�� 2 ���壨�Ӿ��ȶ�����
    {
        Motor_left_Control(0);   // ֹͣ���
        Motor_right_Control(0);
        return; // ����ִ�� PID ����
    }
    pid_cal(&encoder_to_ang);
    pidout_limit(&encoder_to_ang, 3000);
    Motor_left_Control( - encoder_to_ang.out);
    Motor_right_Control( + encoder_to_ang.out);
}


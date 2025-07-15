#ifndef _distance_h
#define _distance_h

#define PI 3.14159265
#define MOTOR_REDUCTION_RATIO 28.0f   // ���ٱ�
#define ENCODER_RESOLUTION 730.0f     // תһȦ������������������*����Ƶ*���ٱ�
									  // 13*2*28 = 728
#define WHEEL_DIAMETER 0.065f		  // ����ֱ��D
#define WHEEL_CIRCUMFERENCE (PI * WHEEL_DIAMETER)  // �����ܳ�=PI*D
#define WHEEL_DIST (WHEEL_CIRCUMFERENCE / ENCODER_RESOLUTION) // ���ӵ�����ǰ������
															  // 3.1416*0.065/730=0.0002797 ��/����
															  //                 �� 0.2797 ����/����		


void get_distance1(void);
void clear_distance1(void);
float get_distance2(void); 

void dist2_pid_control(float dist_tar_cm);
float dist_pid_control(float dist_tar_cm);
void distloop_pid_control(float dist_tar, int base);
void encoder_to_angle(float angle_tar);

#endif
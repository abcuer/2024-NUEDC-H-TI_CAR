#ifndef __PID_h_
#define __PID_h_
#include "headfile.h"

enum
{
  POSITION_PID = 0,  // λ��ʽ
  DELTA_PID,         // ����ʽ
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;

extern pid_t trackLine;
extern pid_t angle;
extern pid_t dist;
extern pid_t encoder_to_ang;

float PID_Increase(pid_t *pid, float Now, float Tar);
void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d);
void pid_clear(pid_t *pid);
void pid_cal(pid_t *pid);
void pidout_limit(pid_t *pid, float duty);

int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
void speed_pid_control(int speed_tar, int base);
void speed2_pid_control(int speed_tar);

void angle_correction(void);
int angle_pid_control(float tar);
void angleloop_pid_control(float angle_tar, int base);

void track_pid_control(float targetValue, float basespeed);
int track2_pid_control(float targetValue);
void trackloop_pid_control(float track_tar, int base);

void dist2_pid_control(float dist_tar_cm);
float dist_pid_control(float dist_tar_cm);
void distloop_pid_control(float dist_tar, int base);

void encoder_to_angle(float angle_tar);
#endif

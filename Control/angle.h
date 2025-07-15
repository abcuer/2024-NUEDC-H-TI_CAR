#ifndef _angle_h
#define _angle_h

void angle_correction(void);
int angle_pid_control(float tar);
void angleloop_pid_control(float angle_tar, int base);

#endif
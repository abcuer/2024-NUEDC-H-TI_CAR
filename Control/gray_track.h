#ifndef _gray_track_h
#define _gray_track_h

void track_pid_control(float targetValue, float basespeed);
int track2_pid_control(float targetValue);
void trackloop_pid_control(float track_tar, int base);

#endif
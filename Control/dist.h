#ifndef _DIST_H
#define _DIST_H

#define PI 3.14159265

typedef struct  {
    float length;   // 周长 (mm) 
    int puise;      // 每圈脉冲数
    float count;    // 每个脉冲代表的距离 (mm) -
}Wheel_Config_s;

void Car_GetDistance(void);

#endif

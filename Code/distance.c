#include "distance.h"

int One_Wheel_len = 204;		 //mm  一轮长度
int One_Wheel_Mai = 730;   	//一圈脉冲数
//  小车一圈实际脉冲1456  (减速比 1:28)
float Wheel_count = 0.2797; //mm 一个脉冲数走的距离
float carL_dis = 0;
float carR_dis = 0;

float dis3 = 1000;  // 1149 - 1151
float dis4 = 1070; 


void distance(void)
{
	carR_dis = Wheel_count * abs(Get_Encoder_countB);
	carL_dis = Wheel_count * abs(Get_Encoder_countA);
}

static int lastCountA = 0;
static int lastCountB = 0;

float get_distance(void)
{
    int currentCountA = Get_Encoder_countA;
    int currentCountB = Get_Encoder_countB;

    int deltaA = abs(currentCountA - lastCountA);
    int deltaB = abs(currentCountB - lastCountB);

    lastCountA = currentCountA;
    lastCountB = currentCountB;

    float deltaDis_mm = Wheel_count * ((float)deltaA + (float)deltaB) / 2.0f;

    return deltaDis_mm / 10.0f; // 返回单位厘米
}


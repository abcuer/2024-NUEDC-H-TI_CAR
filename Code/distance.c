#include "distance.h"

int One_Wheel_len = 204;		 //mm  一轮长度
int One_Wheel_Mai = 730;   	//一圈脉冲数
//  小车一圈实际脉冲1456  (减速比 1:28)
float Wheel_count = 0.2794; //mm 一个脉冲数转长度
float carL_dis = 0;
float carR_dis = 0;

float dis3 = 1000;  // 1149 - 1151
float dis4 = 1070; 


void distance(void)
{
	carR_dis = Wheel_count * fabs(Get_Encoder_countB);
	carL_dis = Wheel_count * fabs(Get_Encoder_countA);
}
#include "distance.h"
#define PI 3.14159265

int One_Wheel_len = 204;		 //mm  һ�ֳ���
int One_Wheel_Mai = 730;   	//һȦ������
float Wheel_count = 0.2794; //mm һ��������ת����
float carL_dis = 0;
float carR_dis = 0;
float dis1 = 1223;  // 1149 - 1151
float dis2 = 1185; 
float dis3 = 1225;  // 1149 - 1151
float dis4 = 1186; 

void distance(void)
{
	carR_dis = Wheel_count * -Get_Encoder_countB;
	carL_dis = Wheel_count * Get_Encoder_countA;
}
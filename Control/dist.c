#include "dist.h"
#include "encoder.h"

Wheel_Config_s wheel ={
	.length = 204,
	.puise = 730,
	.count = 0.2794
};



float dis3 = 1042;  // 1149 - 1151
float dis4 = 996; 

float carL_dis = 0;
float carR_dis = 0;

void Car_GetDistance(void)
{
	carR_dis = wheel.count * -Get_Encoder_countB;
	carL_dis = wheel.count * Get_Encoder_countA;
}

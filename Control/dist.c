#include "dist.h"
#include "encoder.h"

Wheel_Config_s wheel ={
	.length = 204,
	.puise = 730,
	.count = 0.2794
};

float carL_dis = 0;
float carR_dis = 0;

void Car_GetDistance(void)
{
	carR_dis = wheel.count * -Get_Encoder_countB;
	carL_dis = wheel.count * Get_Encoder_countA;
}

#include "board.h"
#include "stdio.h"
#include "string.h"
#include "JY901P.h"
#include "led.h"


extern float Yaw;

float myfabs(float value) {
    if (value < 0) 
	{
        return -value;
    } 
	else 
	{
        return value;
    }
}

//Íù×ó¸º
float Yaw_error(float Target, float Now)
 {
    static float error;
    if (Target >= 0) 
		{
			if (Now <= 0) 
			{
				if(myfabs(Now) < (180 - Target)) 
				{
						error = myfabs(Now) + Target;
				} 
				else 
				{
						error = -(180 - Target) - (180 - myfabs(Now));
				}
			} 
			else 
			{
				if (Now > 0)
				{
					error = Target - Now;
				}
			}
		} 
	 else if (Target < 0)
	 {
 		if (Now > 0) 
		{
			if (Now > Target + 180)
			{
				error = (180 - Now) + (180 - myfabs(Target));
			}
			 else if (Now < Target + 180) 
			{
				error = -(myfabs(Target) + Now);
			}
		} 
		else if (Now < 0) 
		{
			error = -(myfabs(Target) - myfabs(Now));
		}
	 }
				
	return error;
}
		 


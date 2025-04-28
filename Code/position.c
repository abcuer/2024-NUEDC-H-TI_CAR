#include "headfile.h"

uint8_t SoundLight_flag = 0;
uint16_t SoundLight_time = 0;
uint8_t SoundLight_state = 0; 
uint8_t SoundLight_Cnt = 0;
float angle_initial = 0;

void initialize(void) 
{
		LED_Blue_ON();
		delay_ms(50);
		LED_Blue_OFF();
		LED_Green_ON();
		float ang1 = Yaw;
		delay_ms(50);
		float ang2 = Yaw;
		delay_ms(50);
		float ang3 = Yaw;
		angle_initial = (ang1 + ang2 + ang3) / 3;
		first_flag = 1;
		LED_Green_OFF();
		delay_ms(50);
}
 
void SoundLight(void)
{
	if(SoundLight_flag == 0)
	{
		Buzzer_ON();
		LED_Blue_ON();
		SoundLight_flag = 1;
	}
}

void UpdateSoundLight(void)
{
    if(SoundLight_flag)
    {
        SoundLight_time++;

		if(SoundLight_time >= 12) // ???�g?????? 10 ??????
		{
			Buzzer_OFF();
			LED_Blue_OFF();
			SoundLight_time = 0;
			SoundLight_flag = 0; // ?��????????
		}
        
    }
}


#include "soundlight.h"
#include "led.h"
#include "buzzer.h"

static SoundLight_t soundlight = {0};

void SoundLightRun(void)
{
	if(soundlight.flag == 0)
	{
		Buzzer_ON();
		LED_Blue_ON();
		soundlight.flag = 1;
	}
}

void SoundLightUpdate(void)
{
    if(soundlight.flag)
    {
        soundlight.time++;
		if(soundlight.time >= 12) 
		{
			Buzzer_OFF();
			LED_Blue_OFF();
			soundlight.time = 0;
			soundlight.flag = 0; 
		}
    }
}

#include "soundlight.h"
#include "led.h"
#include "beep.h"

static SoundLight_t soundlight = {0};

void SoundLightRun(void)
{
	if(soundlight.flag == 0)
	{
		SetBeepMode(BEEP, BEEP_ON);
		SetLedMode(LED_BLUE, LED_ON);
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
			SetBeepMode(BEEP, BEEP_OFF);
			SetLedMode(LED_BLUE, LED_OFF);
			soundlight.time = 0;
			soundlight.flag = 0; 
		}
    }
}

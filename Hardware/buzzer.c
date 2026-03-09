#include "buzzer.h"

void Buzzer_OFF(void)
{
	DL_GPIO_setPins(LED_PORT, BUZZER_Buzzer_PIN);
}

void Buzzer_ON(void)
{
	DL_GPIO_clearPins(LED_PORT, BUZZER_Buzzer_PIN);
}
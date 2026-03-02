#include "led.h"
//#include "gpio.h"

void LED_Blue_ON(void)
{
	DL_GPIO_setPins(LED_PORT, LED_BLUE_PIN);
}

void LED_Blue_OFF(void)
{
	DL_GPIO_clearPins(LED_PORT, LED_BLUE_PIN);
}

void LED_Green_ON(void)
{
	DL_GPIO_setPins(LED_PORT, LED_GREEN_PIN);
}

void LED_Green_OFF(void)
{
	DL_GPIO_clearPins(LED_PORT, LED_GREEN_PIN);
}

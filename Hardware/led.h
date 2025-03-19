#ifndef _LED_H
#define _LED_H
#include "ti_msp_dl_config.h"
#include "board.h"

void LED_ON(void);
void LED_OFF(void);
void LED_Toggle(void);
void LED_Flash(uint16_t time);
#endif 
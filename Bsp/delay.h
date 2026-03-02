#ifndef _DELAY_H
#define _DELAY_H
#include "stdint.h"

#define MCU_FREQ_MHZ 32

void delay_us(uint32_t nus);
void delay_ms(uint32_t ms);

#endif
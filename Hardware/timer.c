#include "timer.h"

void timerA_init(void)
{
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);	
}

void timerG_init(void)
{
	NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
}
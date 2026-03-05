#include "timer.h"
#include "ti_msp_dl_config.h"

void TimerDeviceInit(void)
{
	// TIM0
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);	
}
#ifndef __UTILS_H
#define __UTILS_H

#include "stdint.h"

typedef enum{
	First = 1,
	Second,
	Third,
	Fourth,
} TASK;

void System_Init(void);
void TaskSelect(void);

extern uint8_t task_num;
extern uint8_t first_flag;
extern uint8_t start_flag;

#endif
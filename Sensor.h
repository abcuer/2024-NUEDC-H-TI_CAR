#ifndef _SENSOR_H
#define _SENSOR_H

#include "board.h"
#include "stdio.h"

extern uint8_t sensor_arr[8];
void sensor_read();
float track_error(void);



#endif
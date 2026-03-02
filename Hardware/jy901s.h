#ifndef __JY901S_H
#define __JY901S_H
#include "ti_msp_dl_config.h"

typedef struct {
	float pitch;
	float roll;
	float yaw;
} EulerAngle_Struct;

void IMU_ParseData(uint8_t data);
void IMU_YawCalibrate(void) ;

extern EulerAngle_Struct jy901s;

#endif

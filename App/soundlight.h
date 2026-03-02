#ifndef __soundlight_h
#define __soundlight_h

#include "stdint.h"

typedef struct
{
	uint8_t flag;
	uint8_t time;
}SoundLight_t;

void SoundLightRun(void);
void SoundLightUpdate(void);

extern float ang_offset;

#endif

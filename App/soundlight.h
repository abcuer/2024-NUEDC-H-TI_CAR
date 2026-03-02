#ifndef __SOUNDLIGHT_H
#define __SOUNDLIGHT_H

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

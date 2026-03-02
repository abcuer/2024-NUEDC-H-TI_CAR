#ifndef _gray_h
#define _gray_h
#include "headfile.h"

typedef struct {
    uint8_t left[4];
    uint8_t right[4];
} GRAY_Struct;

void Gray_Update(void) ;
void Gray_ProcessLine(void);

extern GRAY_Struct gray;

#endif
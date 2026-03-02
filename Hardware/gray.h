#ifndef __GRAY_H
#define __GRAY_H
#include "stdint.h"

#define MAXCNT 3000

typedef struct {
    uint8_t left[4];
    uint8_t right[4];
} GRAY_Struct;

void Gray_Update(void) ;
void Gray_ProcessLine(void);

extern GRAY_Struct gray;
extern int16_t white_time;
extern uint8_t line_flag; 
#endif
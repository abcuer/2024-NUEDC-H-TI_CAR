#ifndef __MYIIC_H_
#define __MYIIC_H_

#include "A_include.h"
#include "board.h"

uint8_t i2c0_write_n_byte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *buf, uint8_t nBytes);


#endif




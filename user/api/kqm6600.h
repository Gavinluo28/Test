#ifndef __KQM6600_H
#define __KQM6600_H
#include "stm32f10x.h"
void uart2_config(void);
void uart2_sendstr(uint8_t str[],uint8_t len);
void analysis2(void);
#endif

#ifndef __UART1_H
#define __UART1_H
#include "stm32f10x.h"
void uart_config(void);
void uart_sendstr(uint8_t str[],uint8_t len);
uint8_t recive_data();
void analysis(void);
#endif

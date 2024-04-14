#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
//pe2  PE3  PE4  PE5   PG6
#define  led1port     GPIOE
#define  led2port     GPIOE
#define  led3port     GPIOE
#define  led4port     GPIOE
#define  led1pin      1<<2
#define  led2pin      1<<3
#define  led3pin      1<<4
#define  led4pin      1<<5
void led_config(void);
void led_configlib(void);
void led_turn(GPIO_TypeDef *ledport,uint16_t ledpin);
void led_off(GPIO_TypeDef *ledport,uint16_t ledpin);
void led_on(GPIO_TypeDef *ledport,uint16_t ledpin);
#endif

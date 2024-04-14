#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"
#define   DHT11_H         GPIO_SetBits(GPIOG, GPIO_Pin_11)
#define   DHT11_L         GPIO_ResetBits(GPIOG, GPIO_Pin_11)
#define   DHT11_STATE     GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11)
typedef struct{
	float hum;
	float tem;
}DHT11;
void get_tem_hum(void);
#endif

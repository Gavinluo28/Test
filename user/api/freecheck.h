#ifndef __freecheck_H
#define __freecheck_H
#include "stm32f10x.h"
#include "stm32f10x.h"              // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "tim6.h"
#include "uart1.h"
#include "stdio.h"
#include "dht11.h"
#include "rgb.h"
#include "adc.h"
#include "kqm6600.h"
#include "su03t.h"
#include "esp8266.h"
#include "RTC.h"
#include "time.h"
#include "bsp_lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "lvgl.h"
#include "lv_port_disp.h"

void Taskstartss(void);
void Hardware(void);
void vApplicationTickHook(void);
void vApplicationStackOverflowHook(void);


#endif

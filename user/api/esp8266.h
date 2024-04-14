#ifndef __ESP8266_H
#define __ESP8266_H
#include "stm32f10x.h"

void esp8266_config(void);
void esp8266_sendstr1(uint8_t str[],uint8_t len);
void esp8266_sendstr(uint8_t str[]);
void get_nettime(void);
void analysis_nettime(void);
void tonet(void);
typedef struct {
	    uint8_t recivebuf[1024];
	    uint16_t recivecnt;
	    uint8_t reciveflag;
	    uint8_t sendbuf[1024];
	    uint16_t sendcnt;
}wifi;
void connect(void);
#endif

#include "MQTT.h"
#include "MQTTPacket.h"
#include "esp8266.h"
#include "string.h"
#include "delay.h"
extern wifi esp8266;
//检查函数  成功返回20  02   失败返回1
uint8_t mqtt_check(uint16_t ms)
{
	while(ms--)
	{
		if(esp8266.reciveflag==1)
		{
			esp8266.reciveflag=0;
			if(esp8266.recivebuf[0]==0x20 && esp8266.recivebuf[1]==0x02)
			{
				return 0;
			}
		}
		delay_ms(1);
		}
	return 1;
}
uint8_t mqtt_connect()
{
	MQTTPacket_connectData options=MQTTPacket_connectData_initializer;
	options.clientID.cstring="k00k3stWNpW.esp8266|securemode=2,signmethod=hmacsha256,timestamp=1689854615341|";
	options.username.cstring="esp8266&k00k3stWNpW";
	options.password.cstring="9da39b13fbf9a936eb4be46a73e1c7c21348f5b702554e58d342201662304df6";
	memset(esp8266.sendbuf,0,sizeof(esp8266.sendbuf));//清空发送缓冲区
	esp8266.sendcnt =0;
	esp8266.sendcnt=MQTTSerialize_connect(esp8266.sendbuf,1024,&options);//将连接报文的内容发送到缓冲区
	memset(esp8266.recivebuf,0,sizeof(esp8266.recivebuf));//清空接收缓冲区
	esp8266.recivecnt =0;
	
	esp8266_sendstr1(esp8266.sendbuf,esp8266.sendcnt);//发送连接报文
  return mqtt_check(1000);
}


uint8_t mqtt_pulish(char *payload)
{
	MQTTString topicName=MQTTString_initializer;
	topicName.cstring="/sys/k00k3stWNpW/esp8266/thing/event/property/post";
	memset(esp8266.sendbuf,0,sizeof(esp8266.sendbuf));
	esp8266.sendcnt =0;
	uint16_t len = strlen(payload);
	esp8266.sendcnt=MQTTSerialize_publish(esp8266.sendbuf,1024,0,0,0,0,topicName,(unsigned char *)payload,len);
	memset(esp8266.recivebuf,0,sizeof(esp8266.recivebuf));//清空接收缓冲区
	esp8266.recivecnt =0;
	esp8266_sendstr1(esp8266.sendbuf,esp8266.sendcnt);//发送连接报文
  return 2;
}

#include "esp8266.h"
#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "delay.h"
#include "MQTT.h"
#include "time.h"
#include <stdlib.h>
#include "dht11.h"
wifi esp8266;
extern time_t lt;
extern DHT11  dht11;
extern uint16_t adc_value[2];
extern float voc;
extern float ch2o;
extern int co2;
extern uint16_t smoke;
extern uint16_t light;


void tonet(void);
//����3����  
//TX--PB10--����-�������������  RX---- PB11 ����--��������   APB1
//PE6  ʹ������    ��ͨ�������   ��ʼ���ø�
void esp8266_config(void)
{
	//��ʼ��GPIO��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE,ENABLE);//����GPIOBʱ��
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PB10 --�����������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PB11 --��������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;;//PE6 --��ͨ�������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//ʹ�����ų�ʼ���ø�
	//��ʼ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//����USART1ʱ��
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=115200;//������115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//ȫ˫��
	USART_InitStruct.USART_Parity= USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//һ��ֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8λ���ݳ���
	USART_Init(USART3 ,&USART_InitStruct);//��ʼ������
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//ʹ�ܴ��ڿ����ж�
	//�����ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART3,ENABLE);//ʹ�ܴ���
}
//���͵����ֽ�
void esp8266_sendbyte(uint8_t data)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==0)//��һ�η����Ƿ����
	{};
	USART_SendData(USART3,data);
}
//���Ͷ���ֽ�
void esp8266_sendstr1(uint8_t str[],uint8_t len)
{
 for(uint8_t i=0;i<len;i++)
	{
	 esp8266_sendbyte(str[i]);
	}
}


//���Ͷ���ֽ�
void esp8266_sendstr(uint8_t str[])
{
	uint8_t i=0;
  while(str[i]!='\0')//�����͵��ַ������鲻����\0˵��������Ϣ�������
	{
	 esp8266_sendbyte(str[i++]);//������
	}
	
}


//uint8_t esp8266_recivebuf[10]={0};//�������ݻ�����
//uint8_t esp8266_recivecnt=0;//�������ݸ���
//uint8_t esp8266_reciveflag=0;//������ɱ�־λ

void USART3_IRQHandler()//�ж�ִ�к�������Ҫ�Լ�д������ճ��
{
	uint8_t data=0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=0)//�����ж�
	{
		data = USART_ReceiveData(USART3);//���������ڽ�������
		USART_SendData(USART1,data);//���͸�����һ
		esp8266.recivebuf[esp8266.recivecnt++]=USART_ReceiveData(USART3);//���������յ������ݴ�ŵ�λ��
	}
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=0)//���������жϣ�˵���жϺ���ִ�����
	{
	  esp8266.reciveflag=1;//��ʱ��־λΪһ
		USART3->SR;
		USART3->DR;//������б�־λ
	}
}

//1.������Ӧ��ATָ��   2.�ж�wifi�Ƿ���ȷ��Ӧ ����---0   �쳣--1
uint8_t sendcmdcheck(char * cmd,char * str,uint16_t ms)
{
//	uint8_t data=2;
	memset(esp8266.recivebuf,0,2048);//��ս��ջ�����
	esp8266.recivecnt =0;//��ս��ռ�����
  esp8266_sendstr((uint8_t *)cmd);//����atָ��
	while(ms--)
	{
	if(esp8266.reciveflag==1)
	{
	 esp8266.reciveflag=0;
		if(strstr((char *)esp8266.recivebuf,str)!=NULL)
		{
		  return 0;//������������
		}
	}
	delay_ms(1);
  }
  return 1;
}
//void connect(void)
//{
//	if(Sendcmdcheck("AT\r\n","OK",1000)==0)//����AT��ȥ���յ����ַ��������OK��˵��ִ�гɹ�
//	{
//		if(Sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
//		{
//			if(Sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
//			{
//				
//			  if(Sendcmdcheck("AT+CIPSTART=\"TCP\",\"iot-06z00efd6u8q668.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",1000)==0)
//				{
//				  if(Sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
//					{
//					 if(Sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
//					 {
//						 if(mqtt_connect()==0)
//							{
//					     printf("���ӳɹ���\r\n");//ע�⣺˫������˫���ű��׵�ǰ����Ҫ��
//								mqtt_pulish("{\"id\":1689856202433,\"params\":{\"temperature\":56,\"Humidity\":89},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}");
//					    }
//					   
//					 }
//					}		
//				}
//			}
//		}
//  }
//}
void connect(void)
{
//char * buf=NULL;
//sprintf(buf,"{\"id\":1689736975893,\"params\":{\"temperature\":%f,\"Humidity\":%f},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.tem,dht11.hum);
if(sendcmdcheck("AT\r\n","OK",1000)==0)
{
	if(sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
	{
		if(sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
		//if(sendcmdcheck("AT+CWJAP=\"013\",\"syq15981832268\"\r\n","OK",10000)==0)
		{
			if(sendcmdcheck("AT+CIPSTART=\"TCP\",\"iot-06z00efd6u8q668.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",10000)==0)
			{
				if(sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
				{
					if(sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
					{

	//						printf("���ӳɹ�!\r\n");
						if(mqtt_connect()==0)
							{
									printf("���ӳɹ�!\r\n");
//									mqtt_subscribe();
//									return 1;
							}
					}
				}
			}
		}
	
	}
	
}

//return 0;
}

extern time_t lt;
void get_nettime(void)
{

	if(sendcmdcheck("AT\r\n","OK",1000)==0)
	{
		if(sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
		{
			if(sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
			{
				if(sendcmdcheck("AT+CIPSTART=\"TCP\",\"api.m.taobao.com\",80\r\n","OK",10000)==0)
				{
					if(sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
					{
						if(sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
						{
							
							esp8266_sendstr((uint8_t *)"GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n");
							
						}
					}
				}
			}
		}		
	}	
}

void  analysis_nettime(void)
{
	
	if(esp8266.reciveflag==1)//�ж��Ƿ�������
	{
		const char nettime[10]={0};
		char * len=0;
		len=strstr((const char *)esp8266.recivebuf,"\"t\":");
		strncpy((char *)nettime,len+5, 13);
		printf("%s\r\n",nettime);
		lt=(atoll(nettime)/1000+(8*3600));
	}
	esp8266.reciveflag=0;
  	
}


char buf[500]={0};
void tonet(void)
{
	sprintf(buf,"{\"id\":1690969048195,\"params\":{\"temperature\":%.2f,\"Humidity\":%.2f,\"LightLux\":%d,\"co2\":%d,\"HCHO\":%.2f,\"TVOC\":%.2f,\"SmokeSensorState\":%d},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.tem,dht11.hum,adc_value[0],co2,ch2o,voc,adc_value[1]);
//		sprintf(buf,"{\"id\":1690969048195,\"params\":{\"temperature\":12,\"Humidity\":13,\"LightLux\":123,\"co2\":123,\"HCHO\":45,\"TVOC\":22,\"SmokeSensorState\":12},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}");

	mqtt_pulish(buf);
	memset(buf,0,500);
}




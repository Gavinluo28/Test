#include "freecheck.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lvgl.h"
#include  "lv_port_disp.h"
#include "key.h"

lv_ui gui_ui;
extern DHT11  dht11;
extern float voc;
extern float ch2o;
extern int co2;
extern uint16_t adc_value[2];
time_t lt=0;

char buftime[256];
char bufdht11tem[256];
char bufdht11hum[256];
char bufco2[100];
char bufvoc[100];
char bufch2o[100];
char buflight[100];
char bufsmoke[100];

TaskHandle_t LEDHandle = NULL;
TaskHandle_t KEYHandle = NULL;
TaskHandle_t DHT11Handle = NULL;
TaskHandle_t BEEPHandle = NULL;
TaskHandle_t ESP8266Handle = NULL;
TaskHandle_t KQM6600Handle = NULL;
TaskHandle_t ADCHandle = NULL;
TaskHandle_t timeHandle = NULL;
TaskHandle_t su_03tHandle = NULL;
TaskHandle_t xLvglTaskHandle = NULL;
SemaphoreHandle_t xSemaphore=NULL;

uint8_t tths1=0;

static lv_style_t style_screen_label_3_main;
static lv_style_t style_screen_label_4_main;
static lv_style_t style_screen_label_5_main;
static lv_style_t style_screen_1_label_1_main;
static lv_style_t style_screen_1_label_2_main;
static lv_style_t style_screen_2_label_3_main;
static lv_style_t style_screen_2_label_4_main;
static lv_style_t style_screen_label_2_main;




void Hardware(void)
{
  NVIC_SetPriorityGrouping(2);//中断分组
  uint8_t key_value=0;
  uint8_t flag=0;
	uint8_t data=0;
  led_configlib();
  key_configlib();
  uart_config();
	rgb_config();
	adc_config();
	
	uart2_config();
	uart_config4();
	rtc_config();
//	printf("sssssss\r\n");
	  esp8266_config();
    
	 delay_ms(2000); 
	connect();
	
//	get_nettime();
		lv_init();
	  lv_port_disp_init();
		

//	xSemaphore=xSemaphoreCreateBinary();
//	if (NULL != xSemaphore)
//	{
//			printf("二值量创建成功!\r\n");
//	}
//	else
//	{
//			printf("二值量创建失败!\r\n");
//	}
//	
}



void LEDTask(void * pvParameters)
{
    while(1)
    {
			switch(tths1)
			{
				case 0: led_off(led4port,led4pin);
								led_on(led1port,led1pin);
								break;
				
				case 1:led_off(led1port,led1pin);
							 led_on(led2port,led2pin);
							  break;
				case 2: led_off(led2port,led2pin);
								led_on(led3port,led3pin);
								break;
				case 3:led_off(led3port,led3pin);
							 led_on(led4port,led4pin);
								break;		  
			 }
			 tths1++;
			 if(tths1==4)
			 {
				 tths1=0;
			 }
				vTaskDelay(500);				
     }
}

void KEYTask(void * pvParameters)
{ 
    while(1)
    {
			 switch(get_valuelib())
			 {
				 case 1:
				        lv_scr_load(gui_ui.screen_1);
							break;
				 case 2:
				        lv_scr_load(gui_ui.screen_2);
							break;
				 case 3:lv_scr_load(gui_ui.screen);
							break;
				 case 4:GPIO_ResetBits(GPIOC, GPIO_Pin_0);
							break;
				 case 5:GPIO_ResetBits(GPIOC, GPIO_Pin_0);
					    break;
			 }	
		   vTaskDelay(20);//任务延时函数
    }
}




void DHT11Task(void * pvParameters)
{
	while(1)
	{
	get_tem_hum();
	sprintf(bufdht11tem,"褰撳墠娓╁害涓�:%.1f鎽勬皬搴� ",dht11.tem);
	sprintf(bufdht11hum,"褰撳墠婀垮害涓�:%.1fRH ",dht11.hum);
  lv_style_set_text_font(&style_screen_1_label_1_main,LV_STATE_DEFAULT, &lv_font_simsun_16);
  lv_label_set_text(gui_ui.screen_1_label_1,bufdht11tem);
  lv_style_set_text_font(&style_screen_1_label_2_main,LV_STATE_DEFAULT, &lv_font_simsun_16);
  lv_label_set_text(gui_ui.screen_1_label_2,bufdht11hum);			
	vTaskDelay(1000);
	}
}

//void BEEPTask(void * pvParameters)
//{
//		while(1)
//		{
//		GPIO_SetBits(GPIOC, GPIO_Pin_0);
//		delay_ms(500);
//	  GPIO_ResetBits(GPIOC, GPIO_Pin_0);
//		vTaskDelay(1000);
//		}
//		
//}
void ESP8266Task(void * pvParameters)
{
	//Delay_ms(2000);
	//connect();
	//Delay_ms(2000);
	while(1)
	{
  tonet();
	vTaskDelay(3000);
	}
	
	
	
}
void KQM6600Task(void * pvParameters)
{
	while(1)
	{		
//	xSemaphoreTake( xSemaphore,portMAX_DELAY);
	analysis2();
	sprintf(bufco2,"浜屾哀鍖栫⒊娴撳害锛�%d ppm ",co2);
	sprintf(bufvoc,"voc娴撳害锛�%.1f mg/m3 ",voc);
	sprintf(bufch2o,"鐢查啗娴撳害锛�%.1f mg/m3 ",ch2o);
	lv_style_set_text_font(&style_screen_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
  lv_label_set_text(gui_ui.screen_label_3,bufco2);
	lv_style_set_text_font(&style_screen_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
  lv_label_set_text(gui_ui.screen_label_4,bufvoc);
	lv_style_set_text_font(&style_screen_label_5_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
  lv_label_set_text(gui_ui.screen_label_5,bufch2o);
	vTaskDelay(1000);
	}

}
void ADCTask(void * pvParameters)
{
	while(1)
	{
	  get_smoke_light(); 
		sprintf(bufsmoke,"褰撳墠鐨勭儫闆炬祿搴︿负锛�%d mg/m3 ",adc_value[1]);
		sprintf(buflight,"褰撳墠鐨勫厜鐓у己搴︿负锛�%d Lux",adc_value[0]);
		lv_style_set_text_font(&style_screen_2_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
    lv_label_set_text(gui_ui.screen_2_label_3,bufsmoke);
		lv_style_set_text_font(&style_screen_2_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
    lv_label_set_text(gui_ui.screen_2_label_4,buflight);
	  vTaskDelay(1000);
	}
	
}
uint32_t ssss;
struct tm  *localtimess={NULL};
void timeTask(void * pvParameters)
{
//	  get_nettime();
//		vTaskDelay(2000);
//	  analysis_nettime();
//		esp8266_sendstr((uint8_t *)"+++");
//	  delay_ms(2000);
//	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
//    PWR_BackupAccessCmd(ENABLE);
//  	RTC_SetCounter(lt);
//	  RTC_WaitForLastTask();
	while(1)
	{
		ssss = RTC_GetCounter();
	  localtimess = localtime((time_t *)&ssss);
	  sprintf(buftime,"%d-%d-%d %d:%d:%d\r\n",localtimess->tm_year+1900,\
	  localtimess->tm_mon+1,localtimess->tm_mday,localtimess->tm_hour,localtimess->tm_min,localtimess->tm_sec);
		lv_style_set_text_font(&style_screen_label_2_main,LV_STATE_DEFAULT, &lv_font_simsun_16);
    lv_label_set_text(gui_ui.screen_label_2,buftime);
		vTaskDelay(1000);
	}
		
}
void su_03tTask(void * pvParameters)
{
	while(1)
	{
	 analysis4();

	 vTaskDelay(1000);
	}
	
}


void vLvglTaskFunction( void * pvParameters )
{	
	 setup_scr_screen(&gui_ui);
   setup_scr_screen_1(&gui_ui);
	 setup_scr_screen_2(&gui_ui);
	 lv_scr_load(gui_ui.screen);
	TickType_t xLastWakeTime;
	const TickType_t	xPeriod = pdMS_TO_TICKS(5);
	while(1)
	{		
		lv_task_handler();
		vTaskDelayUntil(&xLastWakeTime,xPeriod);
	}
}


void Taskstartss(void)
{
	
	  BaseType_t xReturned;
	  xReturned = xTaskCreate(
                    LEDTask,       /* 任务函数名称 */
                    "LED",          /* 任务函数标识符描述性名称 */
                    128,      /* 任务栈空间大小设置 */
                    NULL,    /* 是否作为参数传递 */
                    1,/* 任务优先级设置 */
                    &LEDHandle);      /* 任务句柄 */
	  xReturned = xTaskCreate(
                    KEYTask,       /* 任务函数名称 */
                    "KEY",          /* 任务函数标识符描述性名称 */
                    256,      /* 任务栈空间大小设置 */
                    NULL,    /* 是否作为参数传递 */
                    2,/* 任务优先级设置 */
                    &KEYHandle);      /* 任务句柄 */
	  xReturned = xTaskCreate(
                   BEEPTask,       /* 任务函数名称 */
                    "BEEP",          /* 任务函数标识符描述性名称 */
                     128,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     3,/* 任务优先级设置 */
                    &DHT11Handle);      /* 任务句柄 */
	  xReturned = xTaskCreate(
                    DHT11Task,       /* 任务函数名称 */
                    "DHT11",          /* 任务函数标识符描述性名称 */
                     256,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     4,/* 任务优先级设置 */
                    &DHT11Handle);      /* 任务句柄 */								
		xReturned = xTaskCreate(
                    ESP8266Task,       /* 任务函数名称 */
                    "ESP8266",          /* 任务函数标识符描述性名称 */
                     512,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     11,/* 任务优先级设置 */
                    &ESP8266Handle);      /* 任务句柄 */	
		xReturned = xTaskCreate(
                    KQM6600Task,       /* 任务函数名称 */
                    "KQM6600",          /* 任务函数标识符描述性名称 */
                     512,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     6,/* 任务优先级设置 */
                    &KQM6600Handle);      /* 任务句柄 */								
		xReturned = xTaskCreate(
                   ADCTask,       /* 任务函数名称 */
                    "ADC",          /* 任务函数标识符描述性名称 */
                     512,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     7,/* 任务优先级设置 */
                    &ADCHandle);      /* 任务句柄 */			
    xReturned = xTaskCreate(
                   timeTask,       /* 任务函数名称 */
                    "time",          /* 任务函数标识符描述性名称 */
                     512,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     12,/* 任务优先级设置 */
                    &timeHandle);      /* 任务句柄 */	
    xReturned = xTaskCreate(
                   su_03tTask,       /* 任务函数名称 */
                    "su_03t",          /* 任务函数标识符描述性名称 */
                     512,      /* 任务栈空间大小设置 */
                     NULL,    /* 是否作为参数传递 */
                     9,/* 任务优先级设置 */
                    &su_03tHandle);      /* 任务句柄 */	
    xReturned =xTaskCreate(
								 vLvglTaskFunction,
								 "lvgl_task",
								  1024,
								  NULL, 
								  10,
								  &xLvglTaskHandle);									
    if( xReturned == pdPASS )
    {
			printf("LED任务创建成功\r\n");
			
			vTaskStartScheduler();//启动任务调度器 
    }
			
		while(1)//正常程序不会执行到这里
    {
	  }
}
void vApplicationStackOverflowHook(void)
{
	while(1)
	{
	 printf("任务栈溢出\r\n");
	}
}
void vApplicationTickHook(void)//钩子函数
{
	lv_tick_inc(1);

}

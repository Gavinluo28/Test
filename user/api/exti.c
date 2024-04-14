#include "exti.h"
#include "led.h"
//外部中断配置函数  PA0  PC4---EXTI4--   PC5 ---ETXI5--EXTI9-5     PC6---EXTI6----EXTI9-5
void exti0_config(void)
{
	//PA0  外部中断  PC4  PC5  PC6
	RCC->APB2ENR |= (1<<0);//开启复用时钟
	AFIO->EXTICR[0] &= ~(0Xf<<0);//配置PA0为外部中断
	AFIO->EXTICR[1] &= ~(0Xfff<<0);
	AFIO->EXTICR[1] |= (0X222<<0);
  EXTI->IMR |= (1<<0);//开放中断线0请求
	EXTI->IMR |= (7<<4);//开放中断线4  5  6请求
	EXTI->RTSR |= (1<<0);//设置上升沿触发
	EXTI->FTSR |= (7<<4);//设置下降沿触发
	EXTI->FTSR &= ~(1<<0);//关闭下升沿触发
	EXTI->PR |= (1<<0);//清除挂起位
	EXTI->PR |= (7<<4);//清除挂起位
	//设置中断优先级
	NVIC_SetPriority(EXTI0_IRQn,0);//抢占0   次级0
	NVIC_SetPriority(EXTI4_IRQn,1);//抢占0   次级0
	NVIC_SetPriority(EXTI9_5_IRQn,2);//抢占0   次级0
	NVIC_EnableIRQ(EXTI0_IRQn);//使能中断
	NVIC_EnableIRQ(EXTI4_IRQn);//使能中断
	NVIC_EnableIRQ(EXTI9_5_IRQn);//使能中断
}
void exti0_configlib(void)
{
	//PA0  外部中断  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启复用时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);//PA0   --中断线0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);//PC4   --中断线1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);//PC5   --中断线2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);//PC6   --中断线3
	//外部中断配置
	EXTI_InitTypeDef   EXTI_InitStruct={0};//定义一个结构体变量
	EXTI_InitStruct.EXTI_Line = EXTI_Line0 |EXTI_Line4|EXTI_Line5|EXTI_Line6;//中断线0
	EXTI_InitStruct.EXTI_LineCmd= ENABLE;//使能中断线
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿
	EXTI_Init(&EXTI_InitStruct);//初始化结构体
	//中断优先级
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;//使能优先
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//抢占0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//   次级0
	NVIC_Init(&NVIC_InitStruct);//初始化结构体

	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//抢占0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//   次级0
	NVIC_Init(&NVIC_InitStruct);//初始化结构体

	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//抢占0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//   次级0
	NVIC_Init(&NVIC_InitStruct);//初始化结构体
}


void EXTI0_IRQHandler()
{
	if((EXTI->PR & (1<<0))!=0)//发生中断请求
	{
	  EXTI->PR |= (1<<0);//清除挂起位
		led_on(led1port,led1pin);
	}
}


void EXTI4_IRQHandler()
{
	if((EXTI->PR & (1<<4))!=0)//发生中断请求
	{
	  EXTI->PR |= (1<<4);//清除挂起位
		led_on(led2port,led2pin);
	}
}
void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//发生中断请求
	{
	  EXTI_ClearITPendingBit(EXTI_Line5);//清除挂起位
		led_turn(led3port,led3pin);
	}
	
		if(EXTI_GetITStatus(EXTI_Line6)!=0)//发生中断请求
	{
	  EXTI_ClearITPendingBit(EXTI_Line6);//清除挂起位
		led_turn(led4port,led4pin);
	}
}

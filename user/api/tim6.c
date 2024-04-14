#include "tim6.h"
#include "led.h"
void tim6_config(uint16_t Period,uint16_t Prescaler)
{
	//配置定时器6  APB1  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);//开启定时器6时钟
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = Period-1;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler =Prescaler-1;//预分频器值
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct); 
	TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//使能定时器更新中断
	//设置中断优先级
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM6, ENABLE);//使能定时器6
}
//中断服务函数
void TIM6_IRQHandler()
{
  if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)//判断是否发生更新中断
  {
	 TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		led_turn(led1port,led1pin);
	}
}

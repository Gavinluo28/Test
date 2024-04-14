#include "rgb.h"
void rgb_config()
{
	//PA6 ---B-TIM3-CH1  PA7--G-TIM3-CH2  PA8--R-TIM1-CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启GPIO口和定时器时钟
	//设置GPIO口模式 
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//配置定时器参数
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler =72-1;//预分频器值
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct); //初始化定时器1  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //初始化定时器3
	
	//配置PWM
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置pwm模式
	TIM_OCInitStructure.TIM_Pulse  = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//设置有效电平为低电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能输出
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//使能定时器3第1通道
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//使能定时器3第2通道

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置pwm模式
//	TIM_OCInitStructure.TIM_Pulse  = 0;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//设置有效电平为低电平
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能输出
//	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//使能定时器3第1通道
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//使能定时器1第1通道
  TIM_CtrlPWMOutputs(TIM1,ENABLE);//使能定时器1主输出
	TIM_Cmd(TIM1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void setlight(uint16_t r,uint16_t g, uint16_t b)
{
  TIM_SetCompare1(TIM3,b);
	TIM_SetCompare2(TIM3,g);
	TIM_SetCompare1(TIM1,r);
}
#include "key.h"
#include "delay.h"
//按键I/O配置函数
void key_config(void)
{
	//PA0   PC4  5  6   浮空输入  
	RCC->APB2ENR |= (0x5<<2);//设置第二位  第4位置一
	GPIOA->CRL &= ~(0xF<<0);//清零
	GPIOA->CRL |= (0x4<<0);//浮空输入
	
	GPIOC->CRL &= ~(0xFFF<<16);//清零
	GPIOC->CRL |= (0x444<<16);//浮空输入
}

void key_configlib(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}
//获取按键返回值
uint8_t get_value(void)
{
	uint8_t value=0;
	if((GPIOA->IDR &(1<<0))==1)//按键按下
	{
		delay_ms(10);
		if((GPIOA->IDR &(1<<0))==1)//按键按下
		{
	 while((GPIOA->IDR &(1<<0))==1)//等待按键抬起
	 {   
	 }
	 value=1;
	}
  }
	
	if((GPIOC->IDR &(1<<4))==0)//按键按下
	{
		delay_ms(10);
		if((GPIOC->IDR &(1<<4))==0)//按键按下
		{
	 while((GPIOC->IDR &(1<<4))==0)//等待按键抬起
	 {   
	 }
	 value=2;
	}
  }
  return value;
}

extern uint16_t cnt;
//获取按键返回值
uint8_t get_valuelib(void)
{
	uint8_t value=0;

	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)//按键按下
	{
		delay_ms(10);
		if((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1))//按键按下
		{
			cnt=0;
	 while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)//等待按键抬起
	 {   
	 }
	 if(cnt>3000)
	 {
	  value=5;//长按
	 }
	 else value=1;//短按
	}
  }
	
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//按键按下
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//按键按下
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//等待按键抬起
	 {   
	 }
	 value=2;
	}
  }
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//按键按下
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//按键按下
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//等待按键抬起
	 {   
	 }
	 value=3;
	}
  }
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//按键按下
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//按键按下
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//等待按键抬起
	 {   
	 }
	 value=4;
	}
  }
  return value;
}

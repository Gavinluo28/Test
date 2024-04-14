#include "led.h"
void led_config(void)
{
	//控制led1 亮    PE2 输出低电平
  // PE2  GPIOE  输出  普通  推挽
	RCC->APB2ENR |= (1<<6);//开启GPIOE的时钟
	GPIOE->CRL &= ~(0XFFFF<<8);//把8-23  对应位清零
	GPIOE->CRL |=(0X3333<<8); //把8-21 编成0x03//推挽输出
  //GPIOE->ODR &= ~(0XF<<2);//PE2输出低电平
	GPIOE->ODR |= (0XF<<2);//PE2输出高电平

}

void led_configlib(void)
{
// //开启时钟  GPIOE   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//
//	GPIO_InitTypeDef GPIO_InitStructure = {0};//定义一个结构体变量
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//
//	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
}
//亮灯
void led_on(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR &= ~(ledpin);
}

//灭灯
void led_off(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR |= (ledpin);
}

//反转
void led_turn(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR ^= (ledpin);
}

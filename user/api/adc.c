#include "adc.h"
#include "stdio.h"
#include "dma.h"
extern uint16_t adc_value[2];
void adc_config()
{
	//光照 ---PA5 --ADC12_CH5   烟雾---PC1---ADC1_CH11
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOC,ENABLE);//开启GPIO口和ADC1时钟
	//设置GPIO口模式 
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//设置ADC 
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//6分频   12MHZ
	
	ADC_InitTypeDef ADC_InitStructure={0};
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //扫描
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//不使用外部转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 2;//一个通道
	ADC_Init(ADC1, &ADC_InitStructure);//初始化ADC1
	ADC_Cmd(ADC1,ENABLE);//使能ADC1
	dma_config();
	ADC_DMACmd(ADC1, ENABLE);//开启ADC1的DMA传输请求
	//复位和校验
	ADC_TempSensorVrefintCmd(ENABLE);//开启内部温度检测
	ADC_ResetCalibration(ADC1);//重置ADC校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1)==1);//等待重置完成
	ADC_StartCalibration(ADC1);//开始校准
	while(ADC_GetCalibrationStatus(ADC1)==1);//等待重置完成
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1,ADC_SampleTime_1Cycles5);//设置ADC 通道  采样次序  采样时间
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2,ADC_SampleTime_1Cycles5);//设置ADC 通道  采样次序  采样时间
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//开启软件转换功能
} 

void get_smoke_light()
{
  uint16_t smoke =0;
	uint16_t light =0;
	light =adc_value[0];
	smoke =adc_value[1];
	printf("光照adc值:%d\r\n",light);
  printf("烟雾adc值:%d\r\n",smoke);
}
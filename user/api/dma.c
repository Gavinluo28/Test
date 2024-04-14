#include "dma.h"
uint16_t adc_value[2]={0};
void dma_config(void)
{
	//DMA ---- AHB总线   DMA1_CH1 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能DMA时钟
	DMA_InitTypeDef DMA_InitStruct={0};
	DMA_InitStruct.DMA_BufferSize=2;//缓冲区大小
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;//外设是数据来源
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//不设置内存到内存
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)adc_value;//设置存储器地址
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//半字
	DMA_InitStruct.DMA_MemoryInc= DMA_MemoryInc_Enable;//递增
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//循环模式
	DMA_InitStruct.DMA_Priority= DMA_Priority_Medium;//中优先级
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//不递增
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&(ADC1->DR);//设置外设数据源地址
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);//初始化DMA
  DMA_Cmd(DMA1_Channel1,ENABLE);//使能DMA
}
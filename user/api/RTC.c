#include "RTC.h"
#include "stdio.h"
void NVIC_Configuration(void);
void RTC_Configuration(void);
void Time_Adjust(void);
//配置RTC
void rtc_config(void)
{
	/* NVIC configuration */
  //NVIC_Configuration();//中断设置

  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A1)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    printf("\r\n\n RTC not yet configured....");

    /* RTC Configuration */
    RTC_Configuration();

    printf("\r\n RTC configured....");

    /* Adjust time by values entered by the user on the hyperterminal */
    Time_Adjust();//设置时间

    BKP_WriteBackupRegister(BKP_DR1, 0xA5A1);
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n\n Power On Reset occurred....");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n\n External Reset occurred....");
    }

    printf("\r\n No need to configure RTC....");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}
}	
/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None   中断优先级配置
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure={0};
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks *///使能BKP和电源时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);//使能或者失能 RTC 和后备寄存器访问

  /* Reset Backup Domain */
  BKP_DeInit();//将外设 BKP 的全部寄存器重设为缺省值

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);//设置外部低速晶振（LSE）
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}//等待LSE 晶振就绪

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//选择RTC时钟来源为LSE

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);//使能RTC时钟

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();//等待 RTC 寄存器(RTC_CNT, RTC_ALR and RTC_PRL)与RTC 的 APB 时钟同步

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能秒中断

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成

  /* Set RTC prescaler: set RTC period to 1sec   设置预分频值*/
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成
}

/**
  * @brief  Adjusts time.//调整时间
  * @param  None
  * @retval None
  */
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成
  /* Change the current time */
  RTC_SetCounter(0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成
}


#include "Stepper.h"
#include "delay.h"
#include <stdio.h>
#include <math.h>

void GPIO_Config(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructure; 

	  RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE); 
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE); 

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);    
	
    //GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
    /* Timer2 Channel 1, PA0 */ 
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//FAULT
		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//M2
		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//M1

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);//M0
		
			
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//EN
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//DIR
} 



//================================================================================
void TIM2_Master__TIM3_Slave_Configuration(u32 PulseFrequency) 
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_OCInitTypeDef TIM_OCInitStructure; 
	
	u16 nPDTemp ; 

	TIM_Cmd(TIM2, DISABLE); 
	nPDTemp = 84000UL/PulseFrequency; 			   // 更改频率时，注意处理72000UL及TIM_Prescaler，使TIM_Period不要超过0xFFFF
	
	// 时基配置：配置PWM输出定时器——TIM2 
	/* Time base configuration */ 
	TIM_TimeBaseStructure.TIM_Period = nPDTemp-1; 
	TIM_TimeBaseStructure.TIM_Prescaler = 999; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	// 输出配置：配置PWM输出定时器——TIM2 
	/* PWM1 Mode configuration: Channel1 */    
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = nPDTemp>>1;//50% 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 	
	TIM_ARRPreloadConfig(TIM2, ENABLE); 

	
	// 时基配置：配置脉冲计数寄存器——TIM3 
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 		     
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	// Output Compare Active Mode configuration: Channel1 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0xFFFF; // 这里的配置值意义不大   
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	

	// 配置TIM2为主定时器 
	// Select the Master Slave Mode 
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable); //主模式
	// Master Mode selection  
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update); //更新事件触发
	
	// 配置TIM3为从定时器 
	// Slave Mode selection: TIM3 
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);     //从模式
	TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);          //TIM内部触发1
	TIM_ITRxExternalClockConfig(TIM3, TIM_TS_ITR1);     //设置TIM内部触发为外部时钟模式
//	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE); 		 	 
	
	TIM_Cmd(TIM2, DISABLE); 
	TIM_Cmd(TIM3, DISABLE); 
} 


void Frequence_Setting(u32 PulseFrequency) 
{ 
	u16 nPDTemp ; 
	TIM_Cmd(TIM2, DISABLE); 
	nPDTemp = 84000UL/PulseFrequency; 
	TIM_SetAutoreload(TIM2,nPDTemp);
	TIM_GenerateEvent(TIM2,TIM_EventSource_Update);
	TIM_SetCompare1(TIM2,nPDTemp/2);
	TIM_SetCompare2(TIM2,nPDTemp/2);
}

void Output_Pulse(u16 Num)
{
    TIM3->CCR1 = Num; 
    TIM3->CNT = 0; 
    TIM_Cmd(TIM3, ENABLE); 
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE); 
    TIM_Cmd(TIM2, ENABLE); 
}

void TIM3_IRQHandler(void) 
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) 	   // TIM_IT_CC1
	{ 
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); // 清除中断标志位 
		TIM_Cmd(TIM2, DISABLE); // 关闭定时器 
		TIM_Cmd(TIM3, DISABLE); // 关闭定时器 
		TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE); 
	}
} 

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
  // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
	// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	
	// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	// 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Stepper_Init(void)
{
    NVIC_Config();
	  GPIO_Config();
    GPIO_ResetBits(GPIOD,GPIO_Pin_6);
    GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    GPIO_ResetBits(GPIOE,GPIO_Pin_2);
    GPIO_SetBits(GPIOA,GPIO_Pin_11);	
    GPIO_SetBits(GPIOB,GPIO_Pin_13);//下面
    GPIO_SetBits(GPIOA,GPIO_Pin_12);
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
    GPIO_SetBits(GPIOA,GPIO_Pin_5);		
}

void Stepper1_Degree_90(uint8_t direction)
{
	   if(direction==1)
		 {
              GPIO_SetBits(GPIOB,GPIO_Pin_13);
              GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			        GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	            TIM2_Master__TIM3_Slave_Configuration(250);
					    Output_Pulse(100);
		 }
		 else if(direction==0)
		 {
              GPIO_SetBits(GPIOB,GPIO_Pin_13);
              GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			        GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
	            TIM2_Master__TIM3_Slave_Configuration(250);
					    Output_Pulse(100); 
		 }
		 else Output_Pulse(0);
}

void Stepper2_Degree_90(uint8_t direction)
{
	   if(direction==1)
		 {
              GPIO_SetBits(GPIOA,GPIO_Pin_11);
              GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			        GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	            TIM2_Master__TIM3_Slave_Configuration(30);
					    Output_Pulse(100);
		 }
		 else if(direction==0)
		 {
              GPIO_SetBits(GPIOA,GPIO_Pin_11);
              GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			        GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
	            TIM2_Master__TIM3_Slave_Configuration(30);
					    Output_Pulse(100);
		 }
		 else Output_Pulse(0);
}
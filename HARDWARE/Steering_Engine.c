#include "Steering_Engine.h"

void TIM5_Init(u32 arr,u32 psc)
{        
		GPIO_InitTypeDef GPIO_InitStructure;   
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
		TIM_OCInitTypeDef  TIM_OCInitStructure;     

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;       
		GPIO_Init(GPIOA,&GPIO_InitStructure);   

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	

		TIM_TimeBaseStructure.TIM_Prescaler=psc; 
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		TIM_TimeBaseStructure.TIM_Period=arr;  
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC4Init(TIM5, &TIM_OCInitStructure); 
		TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); 

		TIM_ARRPreloadConfig(TIM5,ENABLE);

		TIM_Cmd(TIM5, ENABLE);                 	
}

void TIM8_Init(u32 arr,u32 psc)
{        
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);          
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
      
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);    
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);   
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
    GPIO_Init(GPIOC,&GPIO_InitStructure);           
      
    TIM_TimeBaseStructure.TIM_Prescaler=psc;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=arr;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;   
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);

    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
      
    TIM_OCInitStructure.TIM_Pulse =0; 
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
		
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
		
    TIM_ARRPreloadConfig(TIM8,ENABLE);
    TIM_Cmd(TIM8, ENABLE); 
    TIM_CtrlPWMOutputs(TIM8, ENABLE);                   	
}

void TIM13_Init(u32 arr,u32 psc)
{        
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;     
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
		GPIO_Init(GPIOA,&GPIO_InitStructure);              
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc; 
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period=arr; 
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		TIM_OC1Init(TIM13, &TIM_OCInitStructure); 

		TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable); 
	 
		TIM_ARRPreloadConfig(TIM13,ENABLE);
		
		TIM_Cmd(TIM13, ENABLE); 			            	
}


void Steering_Motor_Init(void)
{
		TIM5_Init(999,839);
		TIM8_Init(999,1679);
		TIM13_Init(999,839);    
}

void Steering_Cup_Up(uint16_t time)
{
	  TIM8->CCR4=300;
		delay_ms(423);
    TIM8->CCR4=150;
    delay_ms(time);	
    TIM8->CCR4=10;
		delay_ms(360);
	  TIM8->CCR4=0;  
}

void Tea_Chanel_Close(void)
{
     TIM5->CCR4=230;
}

void Tea_Chanel_Open(void)
{
     TIM5->CCR4=150;
}

void Tea_Fall(void)
{
	   uint8_t i;
	   for(i=0;i<4;i++)
	   {
				 TIM13->CCR1=80;
				 delay_ms(700);
				 TIM13->CCR1=250;//     TIM5->CCR4=50;
				 delay_ms(700);
				 TIM13->CCR1=0;
	   }
		 TIM13->CCR1=0;
}

void Cup_UP(void)
{
     TIM8->CCR3=200;
	   delay_ms(500);
     TIM8->CCR3=0;	
}

void Cup_DOWN(void)
{
     TIM8->CCR3=50;
	   delay_ms(500);
     TIM8->CCR3=0;
}

#include "Pomper.h"
#include "delay.h"

void Pomper_Init(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;

     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
     GPIO_Init(GPIOB, &GPIO_InitStructure);
	   GPIO_SetBits(GPIOB,GPIO_Pin_4|GPIO_Pin_6);	
}

void Pomper1_Start(uint16_t time)
{
     GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	   delay_ms(time);
     GPIO_SetBits(GPIOB,GPIO_Pin_4);	
}

void Pomper2_Start(uint16_t time)
{
     GPIO_ResetBits(GPIOB,GPIO_Pin_6);
     delay_ms(time);
     GPIO_SetBits(GPIOB,GPIO_Pin_6);	
}

void Washing_TeaCup(void)
{
    Pomper2_Start(1000); 
}

void Tea_In(void)
{
    Pomper1_Start(10000); 
}

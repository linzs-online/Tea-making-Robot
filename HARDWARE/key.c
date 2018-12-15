/***
	***************************************************************************
	*	@file  	key.c
	*	@version V1.0.0
	*	@brief   按键接口相关函数
   ***************************************************************************
   *  @description
	*
	*  初始化按键引脚，配置为上拉输入、速度等级2M。
	* 	
	***************************************************************************
***/

#include "key.h"  

// 函数：按键IO口初始化
//
void KEY_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE, ENABLE); 	//初始化KEY时钟	
	
	GPIO_InitStructure.GPIO_Pin   =GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度选择
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉	 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   =GPIO_Pin_4|GPIO_Pin_5;	 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度选择  
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;	 	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度选择
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;	 	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度选择
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//上位机结合开启视觉和语音
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度选择
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6;	 	
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
  GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6); 
		
}

// 函数：按键扫描
// 返回：KEY_ON - 按键按下，KEY_OFF - 按键放开 
//			
int	KEY_Scan(void)
{
	/************************************************************************************/
	if( KEY1 == 0 ||KEY2 == 0||KEY3 == 0||KEY4 == 0||
		  KEY5 == 0 ||KEY6 == 0||KEY7 == 0||KEY8 == 0)	//检测按键是否被按下
	{	
	delay_ms(10);	//延时消抖
	if(KEY1==0)
	{
		while(KEY1==0);//等待按键松开
		return 1;
	}
	else if(KEY2==0)
		{
			while(KEY2==0);
			return 2;
		}
	else if(KEY3==0)
		{
			while(KEY3==0);
			return 3;
		}
	else if(KEY4==0)
		{
			while(KEY4==0);
			return 4;
		}
	else if(KEY5==0)
		{
			while(KEY5==0);
			return 5;
		}
	else if(KEY6==0)
		{
			while(KEY6==0);
			return 6;
		}
	else if(KEY7==0)
		{
			while(KEY7==0);
			return 7;
		}
	else if(KEY8==0)
		{
			while(KEY8==0);
			return 8;
		}
	}
	/************************************************************************************/
	else return 9;	
}





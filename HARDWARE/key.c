/***
	***************************************************************************
	*	@file  	key.c
	*	@version V1.0.0
	*	@brief   �����ӿ���غ���
   ***************************************************************************
   *  @description
	*
	*  ��ʼ���������ţ�����Ϊ�������롢�ٶȵȼ�2M��
	* 	
	***************************************************************************
***/

#include "key.h"  

// ����������IO�ڳ�ʼ��
//
void KEY_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE, ENABLE); 	//��ʼ��KEYʱ��	
	
	GPIO_InitStructure.GPIO_Pin   =GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�ѡ��
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����	 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   =GPIO_Pin_4|GPIO_Pin_5;	 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�ѡ��  
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;	 	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�ѡ��
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;	 	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�ѡ��
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//��λ����Ͽ����Ӿ�������
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�ѡ��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6;	 	
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
  GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6); 
		
}

// ����������ɨ��
// ���أ�KEY_ON - �������£�KEY_OFF - �����ſ� 
//			
int	KEY_Scan(void)
{
	/************************************************************************************/
	if( KEY1 == 0 ||KEY2 == 0||KEY3 == 0||KEY4 == 0||
		  KEY5 == 0 ||KEY6 == 0||KEY7 == 0||KEY8 == 0)	//��ⰴ���Ƿ񱻰���
	{	
	delay_ms(10);	//��ʱ����
	if(KEY1==0)
	{
		while(KEY1==0);//�ȴ������ɿ�
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





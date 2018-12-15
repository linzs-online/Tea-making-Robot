#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "delay.h"

#define	KEY_ON	 10		//��������
#define	KEY_OFF	 9		//�����ſ�


#define KEY1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4) //PE2
#define KEY3 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)	//PA0
#define KEY4 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) //PE4
#define KEY5 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)	//PE3 
#define KEY6 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) //PE2
#define KEY7 	  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)	//PA0
#define KEY8 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) //PE4
/*---------------------- �������ú� ------------------------*/

//#define KEY_PIN           GPIO_Pin_15        		 // KEY ����      
#define KEY_PORT          GPIOA                     // KEY GPIO�˿�     


/*---------------------- �������� ----------------------------*/

void 	KEY_Init(void);	//����IO�ڳ�ʼ������
int		KEY_Scan(void);   //����ɨ��

#endif //__KEY_H



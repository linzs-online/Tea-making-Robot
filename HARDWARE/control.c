#include "control.h"
#include "Pomper.h"
#include "Stepper.h"
#include "Steering_Engine.h"

u8 txBuffer1[2]={0xff,0x01};
u8 txBuffer2[2]={0xff,0x02};
u8 txBuffer3[2]={0xff,0x03};
u8 txBuffer4[2]={0xff,0x04};
u8 txBuffer5[2]={0xff,0x05};

void Reset_All(void)
{	
		USART_SendData(USART3,txBuffer5[0]); 
	  delay_ms(10);
		USART_SendData(USART3,txBuffer5[1]);
		delay_ms(10);
		
		USART_SendData(USART3,txBuffer5[0]); 
	  delay_ms(10);
		USART_SendData(USART3,txBuffer5[1]);
		delay_ms(10);
		
		USART_SendData(USART3,txBuffer5[0]); 
	  delay_ms(10);
		USART_SendData(USART3,txBuffer5[1]);
		delay_ms(10);
	  
	  delay_ms(10000);
}

void Choose_Tea(void)
{
	      uint8_t rx=1;
	      switch(rx)
				{		 
					  case 1:
					  {						
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							  break;
					  }
						
					  case 2:
					  {						
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							  break;
					  }
						
					  case 3:
					  {						
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							  break;
					  }
						
					  case 4:
					  {						
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							
						    Stepper1_Degree_90(1);	
						    delay_ms(1000);//选茶
						    GPIO_SetBits(GPIOA,GPIO_Pin_11);
							  break;
					  }
				}
}	

void Washing_ALL(void)
{
	        Washing_TeaCup();//注水洗杯
         	GPIO_ResetBits(GPIOB,GPIO_Pin_13);	
	
				  USART_SendData(USART3,txBuffer1[0]); 
			    delay_ms(20);
			    USART_SendData(USART3,txBuffer1[1]);
				  delay_ms(20);

				  USART_SendData(USART3,txBuffer1[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer1[1]);
					delay_ms(20);

				  USART_SendData(USART3,txBuffer1[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer1[1]);
					delay_ms(20);

		      delay_ms(5000);
          Stepper2_Degree_90(1);					
          delay_ms(5000);//下一个
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
					
			    Washing_TeaCup();//注水洗杯	
         	GPIO_ResetBits(GPIOB,GPIO_Pin_13);					
				  USART_SendData(USART3,txBuffer4[0]); 
			    delay_ms(20);
   		 		USART_SendData(USART3,txBuffer4[1]);
					delay_ms(20);
					
				  USART_SendData(USART3,txBuffer4[0]); 
			    delay_ms(20);
   		 		USART_SendData(USART3,txBuffer4[1]);
					delay_ms(20);
					
				  USART_SendData(USART3,txBuffer4[0]); 
			    delay_ms(20);
   		 		USART_SendData(USART3,txBuffer4[1]);
					delay_ms(20);

					delay_ms(5000);
          Stepper2_Degree_90(1);					
          delay_ms(5000);//下一个	
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
					
			    Washing_TeaCup();//注水洗杯
         	GPIO_ResetBits(GPIOB,GPIO_Pin_13);							
				  USART_SendData(USART3,txBuffer3[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer3[1]);
					delay_ms(20);
					
				  USART_SendData(USART3,txBuffer3[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer3[1]);
					delay_ms(20);
					
				  USART_SendData(USART3,txBuffer3[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer3[1]);
					delay_ms(20);

					delay_ms(5000);				
          Stepper2_Degree_90(1);					
          delay_ms(5000);//下一个
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);

			    Washing_TeaCup();//注水洗杯	
					GPIO_ResetBits(GPIOB,GPIO_Pin_13);		
				  USART_SendData(USART3,txBuffer2[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer2[1]);
					delay_ms(20);
					
				  USART_SendData(USART3,txBuffer2[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer2[1]);
					delay_ms(20);
					
					USART_SendData(USART3,txBuffer2[0]); 
			    delay_ms(20);
			 		USART_SendData(USART3,txBuffer2[1]);
					delay_ms(20);

					delay_ms(5000);				
          Stepper2_Degree_90(1);					
          delay_ms(5000);//下一个	
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void Make_Tea(void)
{
					Steering_Cup_Up(700);//注茶
				  Stepper2_Degree_90(0);
					delay_ms(5000);
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);

					Steering_Cup_Up(700);//注茶
				  Stepper2_Degree_90(0);
					delay_ms(5000);
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
					
					Steering_Cup_Up(700);//注茶
				  Stepper2_Degree_90(0);
					delay_ms(5000);
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
					
					Steering_Cup_Up(700);//注茶
				  Stepper2_Degree_90(0);
					delay_ms(5000);
				  GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void Making_Tea_All(void)
{
     Reset_All();
	   Choose_Tea();
	
	   Cup_UP(); //开茶杯	 
		 Tea_Chanel_Open();//茶叶通道开
 		 Tea_Fall();//扫茶
	   delay_ms(1000);
		 Tea_Chanel_Close();//茶叶通道关
	   Cup_DOWN();//合上盖子
 			 
		 delay_ms(500);
		 Tea_In();//注水泡茶
		 delay_ms(20000);//泡茶
     Washing_ALL();
	
	   Make_Tea();   
}
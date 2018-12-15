#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "control.h"
#include "Steering_Engine.h"
#include "Stepper.h"
#include "lcd_3.5tft.h"
#include "sys.h"
#include "Pomper.h"
#include "key.h"

void LCD_ClearTest(void);			// 清屏测试
void LCD_TextTest(void);			// 文本显示测试
void LCD_FillTest(void);			// 矩形填充测试
void LCD_ColorTest(void);			// 颜色测试
void LCD_GrahicTest(void);			// 绘图测试
void LCD_HorizontalText(void);	// 横屏测试
extern u8 TIM2_Pulse_TIM3_Counter_OK;
extern u8 USART5_RX_BUF[USART5_REC_LEN]; 

u8 raspberry_data;
u8 stm32_f1_data;

extern u8 USART3_RX_BUF[USART3_REC_LEN];  
extern u8 USART_RX_BUF[USART_REC_LEN]; 
int main(void)
{
	  int key,i,Flag=0;
	  uint8_t u;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//???????????2
		uart_init(115200);
	  USART3_init(115200);
		delay_init(168);	  
	  Stepper_Init();
    Steering_Motor_Init();
	  Pomper_Init();
	  KEY_Init();
	
/********************************************/	
  	LCD_Init();		// LCD初始化	 
	  LCD_SetBackColor(LCD_WHITE);
	  LCD_Clear(); //清屏，刷背景色	
  	LCD_SetFont(&Font32);			// 设置字体	
    LCD_SetColor(LCD_BLACK);	//设置画笔颜色	
	  LCD_DisplayMode(Mode_H);
/***********************************************/
	
    Making_Tea_All();
	  while(1)
		{
		  raspberry_data = USART_ReceiveData(USART3);
			if (raspberry_data != 0)
			{
				USART_SendData(USART3,raspberry_data);
				switch(raspberry_data)
				{
					case 1://视觉铁观音;break;
					case 2://视觉单纵茶
					case 3://视觉大红袍
					case 4://视觉水仙茶
					case 5://视觉冲茶
					case 6://语言铁观音
					case 7://语音水仙茶
					case 8://语音单纵茶
					case 9://语音大红袍
					case 10://语音冲茶
					case 16://视觉洗杯子
					case 17://语音洗杯子
					default:break;		
				}
			}//返回值
       key=KEY_Scan();
	     if(key==1)
			 { 
				Flag = 2;
			  if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)== 1)
				{
					GPIO_ResetBits(GPIOE, GPIO_Pin_0);
					LCD_Clear(); 
					LCD_DisplayText(172,80,"关闭手势识别",LCD_WHITE);
				}
				else
				{
					GPIO_SetBits(GPIOE, GPIO_Pin_0);
					LCD_Clear();
					LCD_DisplayText(172,80,"手势识别中",LCD_WHITE);
				} 
			 }        //手势识别中
	     else if(key==2)
				{ 
					Flag = 2;  
					if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)== 1)
					{
						GPIO_ResetBits(GPIOE, GPIO_Pin_6);
						LCD_Clear();
						LCD_DisplayText(172,80,"关闭语音识别",LCD_WHITE);
					}
					else
					{
						GPIO_SetBits(GPIOE, GPIO_Pin_6);
						LCD_Clear();
						LCD_DisplayText(172,80,"语音识别中",LCD_WHITE);
					}
				}       //语音识别中
       //else if(key==3){ Flag = 2;printf("%d",13);GPIO_SetBits(GPIOE, GPIO_Pin_5);LCD_Clear();LCD_DisplayText(100,80,"手势语音融合识别中",LCD_WHITE); } //手势语音融合识别中	 
	     else if(key==4)                                                         //泡茶
	  {
			printf("%d",14);
			 i = 1;
			 Flag = 1;
			 LCD_Clear(); //清屏，刷背景色
			 LCD_DisplayText(140,0,"茶叶选择界面",LCD_WHITE);
			 LCD_DisplayText(188,40,"铁观音",LCD_WHITE);
			 LCD_DisplayText(188,80,"单丛茶",LCD_WHITE);
			 LCD_DisplayText(188,120,"水仙茶",LCD_WHITE);
			 LCD_DisplayText(188,160,"大红袍",LCD_WHITE);
	  }
	 
/**********************菜单向上向下选择***********************************/	 	 
	 else if(key==5)                                                           //向上选择
	 { 
			i++;		
	 }
   else if(key==6)                                                           //向下选择
	 {
	   i--;
	 }	
/************************************************************************/	

   else if(key==7) 
     {
			 Flag=2;  
			 LCD_Clear();
			 LCD_DisplayText(172,80,"洗杯中",LCD_WHITE); 
		 }    //洗杯
	  
	 else if(key==8) 
    {
			Flag=2;
		  LCD_Clear();
		  LCD_DisplayText(172,80,"泡茶中",LCD_WHITE); 
		}      		//确认
	 
/**********按键光标向上向下选择处理**************************************/
/************************************************************************/	 
		 if(i<1&&Flag ==1)
			{
				i=4;
			}
		if(i>=5&&Flag ==1)
		 {
			i=1;
		 }	   		
	  if(i==1&&Flag ==1)
			 {  
				LCD_DisplayText(140,0,"茶叶选择界面",  LCD_WHITE);
				LCD_DisplayText(188,40,"铁观音",LIGHT_GREY);
				LCD_DisplayText(188,80,"单丛茶",LCD_WHITE);
				LCD_DisplayText(188,120,"水仙茶",LCD_WHITE);
				LCD_DisplayText(188,160,"大红袍",LCD_WHITE);
			 }
	  if(i==2&&Flag ==1)
			{ 
				LCD_DisplayText(140,0,"茶叶选择界面",  LCD_WHITE);
				LCD_DisplayText(188,40,"铁观音",LCD_WHITE);
				LCD_DisplayText(188,80,"单丛茶",LIGHT_GREY);
				LCD_DisplayText(188,120,"水仙茶",LCD_WHITE);
				LCD_DisplayText(188,160,"大红袍",LCD_WHITE);
			}
		if(i==3&&Flag ==1)
			{
				LCD_DisplayText(140,0,"茶叶选择界面",  LCD_WHITE);
				LCD_DisplayText(188,40,"铁观音",LCD_WHITE);
				LCD_DisplayText(188,80,"单丛茶",LCD_WHITE);
				LCD_DisplayText(188,120,"水仙茶",LIGHT_GREY);
				LCD_DisplayText(188,160,"大红袍",LCD_WHITE);
			}
		if(i==4&&Flag ==1)
			{
				LCD_DisplayText(140,0,"茶叶选择界面",  LCD_WHITE);
				LCD_DisplayText(188,40,"铁观音",LCD_WHITE);
				LCD_DisplayText(188,80,"单丛茶",LCD_WHITE);
				LCD_DisplayText(188,120,"水仙茶",LCD_WHITE);
				LCD_DisplayText(188,160,"大红袍",LIGHT_GREY);
			}
		}
}	 
/************************************************************************/   

//		Pomper2_Start(1000);
//    delay_ms(500);
//    Pomper1_Start(1000);
//    delay_ms(500);		
/************************************************************************/
			 
				
			  //MSD3_Move(32000,200,200,1000);
			  //TIM1->CCR3=40;
			  //delay_ms(1000);
			  //TIM1->CCR3=0;
//for(i=0;i<200;i++)
//			  {
//			      TIM5->CCR4=150-0.5*i;
//            delay_ms(4);					
//			  }
//				delay_ms(500);
//				for(i=0;i<100;i++)
//			  {
//			      TIM5->CCR4=50+i;
//            delay_ms(3);					
//			  
//				}
//				delay_ms(500);

//     TIM5->CCR4=50;
//     delay_ms(700);
//TIM5->CCR4=250;
//delay_ms(700);

			 //TIM_SetCompare2(TIM9,150);
       		//delay_ms(255);
			//TIM_SetCompare2(TIM9,0);
			//delay_ms(1000);
	//	a=TIM3->CNT;
		//if(TIM2_Pulse_TIM3_Counter_OK == 0)
		  //Output_Pulse(5);
			//TIM_SetCompare2(TIM2,0);
			//delay_ms(50);
		//else if(TIM2_Pulse_TIM3_Counter_OK == 2)
		//{
			//for(i=0; i<100000; i++);				// delay
			//TIM2_Pulse_TIM3_Counter_OK = 1;
		//


        //delay_ms(10000);			
	  

/*
手册中讲解到步骤15的时候的main.c源码如下：
#include "stm32f4xx.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
  
void delay(__IO uint32_t nCount);

void delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while(1){
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		delay(0x7FFFFF);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		delay(0x7FFFFF);
	
	}
}
*/


//	  TIM_SetCompare3(TIM1,300);
//		delay_ms(423);
//    TIM_SetCompare3(TIM1,150);
//	  delay_ms(500);
//    TIM_SetCompare3(TIM1,10);
//		delay_ms(360);
//Steering motor1
//        for(i=0;i<200;i++)
//			  {
//			      TIM5->CCR4=150-0.5*i;
//            delay_ms(4);					
//			  }
//				delay_ms(500);
//				for(i=0;i<100;i++)
//			  {
//			      TIM5->CCR4=50+i;
//            delay_ms(3);					
//			  
//				}
//				delay_ms(500);

//Steering motor2
//        for(i=0;i<200;i++)
//			  {
//			      TIM5->CCR4=150-0.5*i;
//            delay_ms(4);					
//			  }
//				delay_ms(500);
//				for(i=0;i<100;i++)
//			  {
//			      TIM5->CCR4=50+i;
//            delay_ms(3);					
//			  
//				}
//				delay_ms(500);

//MOTOR3
//        for(i=0;i<200;i++)
//			  {
//			      TIM5->CCR4=150-0.5*i;
//            delay_ms(4);					
//			  }
//				delay_ms(500);
//				for(i=0;i<100;i++)
//			  {
//			      TIM5->CCR4=50+i;
//            delay_ms(3);					
//			  
//				}
//				delay_ms(500);

// MOTOR4       
//for(i=0;i<200;i++)
//			  {
//			      TIM5->CCR4=150-0.5*i;
//            delay_ms(4);					
//			  }
//				delay_ms(500);
//				for(i=0;i<100;i++)
//			  {
//			      TIM5->CCR4=50+i;
//            delay_ms(3);					
//			  
//				}
//				delay_ms(500);





/*---------------------------- 显示屏测试函数 ---------------------------------*/
// 函数：清屏测试
//
void LCD_ClearTest(void)
{
	u16 time = 1000;	//延时时间

	LCD_SetFont(&Font24);		//设置字体
	LCD_SetColor(LCD_BLACK);	//设置画笔颜色

	LCD_SetBackColor(LCD_RED);    LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_GREEN);  LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_BLUE);   LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_GREY);   LCD_Clear();  delay_ms(time);	
	LCD_SetBackColor(LCD_WHITE);   LCD_Clear();  delay_ms(time);
	LCD_SetBackColor(LCD_BLACK);   LCD_Clear();  delay_ms(time);
}
// 函数：文本测试
//
void LCD_TextTest(void)
{
	u16 time = 100;
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.01"); 				delay_ms(time);		
	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.01234"); 			delay_ms(time);
	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.012345"); 		delay_ms(time);	
	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.01234567"); 		delay_ms(time);	
	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	

	LCD_SetColor(LCD_CYAN);                                                      
	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	
	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.01234567"); 	delay_ms(time);	
	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.012345"); 		delay_ms(time);		
	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.01234"); 		delay_ms(time);		
	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.01"); 			delay_ms(time);	

	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayNumber( 0,220,429496729,9);   delay_ms(time);	
	LCD_ShowNumMode(Fill_Zero);	
	LCD_DisplayNumber( 0,252,123456,9);	     delay_ms(time);
	LCD_ShowNumMode(Fill_Space);	
	LCD_DisplayNumber( 0,284,1234,9);		  delay_ms(time);		

	delay_ms(2000);	
}

// 函数：矩形填充测试
//
void LCD_FillTest(void)
{
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(110,  3,130,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(110, 25,130,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(110, 47,130,16);  LCD_DisplayString(0, 47,"LCD_RED");			
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(110, 69,130,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(110, 91,130,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(110,113,130,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(110,135,130,16);	LCD_DisplayString(0,135,"LCD_GREY");		
                                      
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(110,157,130,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(110,179,130,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(110,201,130,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(110,223,130,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(110,245,130,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(110,267,130,16);  LCD_DisplayString(0,267,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(110,289,130,16);	LCD_DisplayString(0,289,"LIGHT_GREY");  	
                                                     
	delay_ms(2000);
}

// 函数：颜色测试
//
void LCD_ColorTest(void)
{
	u16 i;

	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_BLACK);

	LCD_SetBackColor(LIGHT_MAGENTA); LCD_DisplayString(0,  0,"   Color Test   "); 
	LCD_SetBackColor(LCD_YELLOW);  	LCD_DisplayString(0, 40,"   Color Test   ");
	LCD_SetBackColor(LCD_CYAN);  	 	LCD_DisplayString(0, 80,"   Color Test   ");

	//使用画线函数绘制三基色色条
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
		LCD_DrawLine(i,150,i,190);			
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
		LCD_DrawLine(i,200,i,240);	
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
		LCD_DrawLine(i,250,i,290);	
	}	
	delay_ms(2000);	
}
// 函数：绘图测试
//
void LCD_GrahicTest(void)
{
	u16 time = 80;

	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	

	LCD_SetColor(LCD_RED);
	LCD_DrawLine(0,10,240,10);	delay_ms(time);	//画直线
	LCD_DrawLine(0,20,240,20);	delay_ms(time);
	LCD_DrawLine(0,30,240,30); delay_ms(time);
	LCD_DrawLine(0,40,240,40);	delay_ms(time);	
	
	LCD_SetColor(LCD_YELLOW);	
	LCD_DrawRect( 5, 85,240,150); delay_ms(time);	//绘制矩形
	LCD_DrawRect(30,100,190,120); delay_ms(time);
	LCD_DrawRect(55,115,140,90);  delay_ms(time);
	LCD_DrawRect(80,135,90,60);   delay_ms(time);	

	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(120,170,100);	delay_ms(time);	//绘制圆形
	LCD_DrawCircle(120,170,80);   delay_ms(time);
	LCD_DrawCircle(120,170,60);   delay_ms(time);
	LCD_DrawCircle(120,170,40);   delay_ms(time);

	LCD_SetColor(DARK_CYAN);
	LCD_DrawLine(0,285,240,285);	delay_ms(time);	//画直线
	LCD_DrawLine(0,295,240,295);	delay_ms(time);
	LCD_DrawLine(0,305,240,305);  delay_ms(time);
	LCD_DrawLine(0,315,240,315);	delay_ms(time);	
	delay_ms(1000);

	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	
	
	LCD_SetColor(LCD_RED);    LCD_FillCircle( 60,80,60);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(120,80,60); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(160,80,60);  	

	LCD_SetColor(LIGHT_BLUE);
	LCD_DrawEllipse(120,250,110,50);  delay_ms(time);	//绘制椭圆
	LCD_DrawEllipse(120,250, 95,40);  delay_ms(time);
	LCD_DrawEllipse(120,250, 80,30);  delay_ms(time);
	LCD_DrawEllipse(120,250, 65,20);  delay_ms(time);

	delay_ms(2000);	
}

void LCD_HorizontalText(void)
{
	u16 time = 100;
	
	LCD_ClearTest();	// 清屏测试函数

	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.0123456"); 		delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:"); 	delay_ms(time);	// 字符显示测试
	LCD_SetColor(LIGHT_YELLOW);                                                      
	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// 字符显示测试
	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// 字符显示测试	
	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456789:"); delay_ms(time);	// 字符显示测试	
	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.0123456"); 		delay_ms(time);	// 字符显示测试
	delay_ms(2000);		
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(110,  3,210,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		// 矩形填充测试
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(110, 25,210,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		// 矩形填充测试
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(110, 47,210,16);  LCD_DisplayString(0, 47,"LCD_RED");			// 矩形填充测试
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(110, 69,210,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		// 矩形填充测试
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(110, 91,210,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	// 矩形填充测试
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(110,113,210,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		// 矩形填充测试
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(110,135,210,16);	LCD_DisplayString(0,135,"LCD_GREY");		// 矩形填充测试
                                                     
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(110,157,210,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		// 矩形填充测试
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(110,179,210,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	// 矩形填充测试
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(110,201,210,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   // 矩形填充测试
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(110,223,210,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   // 矩形填充测试                                         
	delay_ms(2000);	
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色		
	LCD_SetColor(LCD_RED);    LCD_FillCircle( 80,120,80);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(160,120,80); 	//填充圆形
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(240,120,80);  	//填充圆形
	delay_ms(2000);		
}




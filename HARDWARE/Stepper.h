#ifndef __STEPPER_H
#define __STEPPER_H

#include "sys.h"

//#define CW  0
//#define CCW 1

//#define TRUE 1
//#define FALSE 0

//#define Pulse_width 20

//  //ϵͳ״̬
//struct GLOBAL_FLAGS3 {
//  //�����������������ʱ��ֵΪ1
//  unsigned char running:1;
//  //�����ڽ��յ�����ʱ��ֵΪ1
//  unsigned char cmd:1;
//  //���������������ʱ,ֵΪ1
//  unsigned char out_ena:1;
//};

//extern struct GLOBAL_FLAGS3 status3;
//extern int stepPosition3;
//extern signed int p_step3;
//extern unsigned int p_accel;
//extern unsigned int p_decel;
//extern unsigned int p_speed3;

//#define T1_FREQ 1000000     //��ʱ��Ƶ�ʣ���PWM�ź�Ƶ�ʣ�
//#define FSPR    400         //���������Ȧ����
//#define SPR     (FSPR*8)//*100)  //100ϸ�ֵĲ��� steps per round
//// ��ѧ������ ����MSD_Move�����ļ򻯼���
//#define ALPHA (2*3.14159/SPR)                    // 2*pi/spr
//#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))     // (ALPHA / T1_FREQ)*100
//#define T1_FREQ_148 ((int)((T1_FREQ*0.676)/100)) // divided by 100 and scaled by 0.676
//#define A_SQ (long)(ALPHA*2*10000000000)         // 
//#define A_x20000 (int)(ALPHA*20000)              // ALPHA*20000
//    
////�ٶ�����״̬
//#define STOP  0
//#define ACCEL 1
//#define DECEL 2
//#define RUN   3

//typedef struct {
//  //�������״̬
//  unsigned char run_state : 3;
//  //������з���
//  unsigned char dir : 1;
//  //��һ��������ʱ���ڣ�����ʱΪ���ٶ�����
//  unsigned int step_delay;
//  //��ʼ���ٵ�λ��
//  unsigned int decel_start;
//  //���پ���
//  signed int decel_val;
//  //��С��ʱ��������ٶȣ�
//  signed int min_delay;
//  //���ٻ��߼��ټ�����
//  signed int accel_count;
//} speedRampData3;


//// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
//// ��������ʹ�ö�ʱ��TIM2
//#define            MSD3_PULSE_TIM                    TIM4
//#define            MSD3_PULSE_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
//#define            MSD3_PULSE_TIM_CLK                RCC_APB1Periph_TIM4
//// ��ʱ�����PWMͨ����PA0��ͨ��1
//#define            MSD3_PULSE_OCx_Init               TIM_OC1Init
//#define            MSD3_PULSE_OCx_PreloadConfig      TIM_OC1PreloadConfig
//// ��ʱ���ж�
//#define            MSD3_PULSE_TIM_IRQ                TIM4_IRQn
//#define            MSD3_PULSE_TIM_IRQHandler         TIM4_IRQHandler

//// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
//#define            MSD3_PULSE_TIM_PERIOD             (10-1)
//#define            MSD3_PULSE_TIM_PSC                (84-1)

//// ��������������ͨ��
//#define            MSD3_PULSE_GPIO_CLK               RCC_AHB1Periph_GPIOD
//#define            MSD3_PULSE_PORT                   GPIOD
//#define            MSD3_PULSE_PIN                    GPIO_Pin_12

//// ��������������
//#define            MSD3_DIR_GPIO_CLK                 RCC_AHB1Periph_GPIOB
//#define            MSD3_DIR_PORT                     GPIOB
//#define            MSD3_DIR_PIN                      GPIO_Pin_9

//// ����������ʹ������
//#define            MSD_ENA_GPIO_CLK                 RCC_AHB1Periph_GPIOB
//#define            MSD_ENA_PORT                     GPIOB//C
//#define            MSD_ENA_PIN                      GPIO_Pin_4


//#define DIR3(a)	if (a == CW)	\
//					GPIO_ResetBits(MSD3_DIR_PORT,MSD3_DIR_PIN);\
//					else		\
//					GPIO_SetBits(MSD3_DIR_PORT,MSD3_DIR_PIN)
//                    
///**************************��������********************************/

//void MSD3_Init(void);
//void MSD3_ENA(FunctionalState NewState);
//void MSD3_Move(signed int step, unsigned int accel, unsigned int decel, unsigned int speed);
					
void GPIO_Config(void);
void TIM2_Master__TIM3_Slave_Configuration(u32 PulseFrequency);
void Frequence_Setting(u32 PulseFrequency);	
void Output_Pulse(u16 Num);	
void NVIC_Config(void);	
void Stepper_Init(void);
void Stepper1_Degree_90(uint8_t  direction);
void Stepper2_Degree_90(uint8_t direction);
#endif



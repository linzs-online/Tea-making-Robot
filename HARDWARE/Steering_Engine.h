#ifndef __Steering_Engine_H
#define __Steering_Engine_H

#include "sys.h"

void Steering_Motor_Init(void);
void TIM9_Init(u32 arr,u32 psc);
void TIM4_Init(u32 arr,u32 psc);
void TIM12_Init(u32 arr,u32 psc);
void TIM14_Init(u32 arr,u32 psc);
void TIM5_Init(u32 arr,u32 psc);
void TIM8_Init(u32 arr,u32 psc);
void TIM13_Init(u32 arr,u32 psc);
void Steering_Cup_Up(uint16_t time);
void Steering_Cup_Down(void);
void Tea_Fall(void);
void Tea_Chanel_Open(void);
void Tea_Chanel_Close(void);
void Cup_UP(void);
void Cup_DOWN(void);
#endif
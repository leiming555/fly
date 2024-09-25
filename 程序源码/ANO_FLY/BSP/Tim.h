#ifndef _BSP__TIM_H_
#define _BSP__TIM_H_
#include "stm32f10x.h"

extern u32 TIM3_IRQCNT;
void Tim3_Init(u16 period_num);//用于精确延时
//void Tim7_Init(u16 period_num);//用于精确延时
//extern u32 TIM7_IRQCNT;

#endif

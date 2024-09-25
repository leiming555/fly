#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_
#include "stm32f10x.h"

void Tim3_Init(u16 period_num);//用于精确延时
void Tim2_Init(void);

#endif

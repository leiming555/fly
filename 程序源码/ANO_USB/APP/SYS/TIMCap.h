#ifndef __TIMCAP_H
#define __TIMCAP_H

#include "stm32f10x.h" 

void TIM1_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM1_CO1_Check(u16 *frequency,u16 *percent);		// PA8
u8 	TIM1_CO2_Check(u16 *frequency,u16 *percent);		// PA9
u8 	TIM1_CO3_Check(u16 *frequency,u16 *percent);		// PA10
u8 	TIM1_CO4_Check(u16 *frequency,u16 *percent);		// PA11

void TIM2_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM2_CO1_Check(u16 *frequency,u16 *percent);		// PA0
u8 	TIM2_CO2_Check(u16 *frequency,u16 *percent);		// PA1
u8 	TIM2_CO3_Check(u16 *frequency,u16 *percent);		// PA2
u8 	TIM2_CO4_Check(u16 *frequency,u16 *percent);		// PA3

void TIM3_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM3_CO1_Check(u16 *frequency,u16 *percent);		// PA6
u8 	TIM3_CO2_Check(u16 *frequency,u16 *percent);		// PA7
u8 	TIM3_CO3_Check(u16 *frequency,u16 *percent);		// PB0
u8 	TIM3_CO4_Check(u16 *frequency,u16 *percent);		// PB1

void TIM4_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM4_CO1_Check(u16 *frequency,u16 *percent);		// PB6
u8 	TIM4_CO2_Check(u16 *frequency,u16 *percent);		// PB7
u8 	TIM4_CO3_Check(u16 *frequency,u16 *percent);		// PB8
u8 	TIM4_CO4_Check(u16 *frequency,u16 *percent);		// PB9

void TIM5_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM5_CO1_Check(u16 *frequency,u16 *percent);		// PA0
u8 	TIM5_CO2_Check(u16 *frequency,u16 *percent);		// PA1
u8 	TIM5_CO3_Check(u16 *frequency,u16 *percent);		// PA2
u8 	TIM5_CO4_Check(u16 *frequency,u16 *percent);		// PA3

void TIM8_Cap_Init(u16 Prescaler,u16 Period,u8 OC);
u8 	TIM8_CO1_Check(u16 *frequency,u16 *percent);		// PC6
u8 	TIM8_CO2_Check(u16 *frequency,u16 *percent);		// PC7
u8 	TIM8_CO3_Check(u16 *frequency,u16 *percent);		// PC8
u8 	TIM8_CO4_Check(u16 *frequency,u16 *percent);		// PC9


#endif

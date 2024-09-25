#ifndef _LED_H_
#define _LED_H_

#include "tim.h"		

#define LED1_OFF  	GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED1_ON 		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED2_OFF  	GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define LED2_ON 		GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define LED3_OFF  	GPIO_SetBits(GPIOB, GPIO_Pin_3)
#define LED3_ON 		GPIO_ResetBits(GPIOB, GPIO_Pin_3)
#define LED4_OFF  	GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define LED4_ON 		GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define LEDALL_OFF  GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 );LED4_OFF;
#define LEDALL_ON 	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 );LED4_ON;

void LED_INIT(void);
void LED_FLASH(void);
void LED1_ONOFF(void);
void LED2_ONOFF(void);

#endif

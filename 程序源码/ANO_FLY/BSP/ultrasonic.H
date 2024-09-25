#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
//#include "sys.h"
#include <stm32f10x.h>

#include "stm32_config.h"
//#define u32 unsigned 
#define TRIG_H GPIO_SetBits  (ULTRASONIC_TRIG_GPIO,ULTRASONIC_TRIG_PIN)
#define TRIG_L GPIO_ResetBits(ULTRASONIC_TRIG_GPIO,ULTRASONIC_TRIG_PIN)
extern void Ultrasonic_Init(void);
//u32 ultrasonic (void);
u32 Ultrasonic_ECHO (void);
void Ultrasonic_TRIG (void);

// extern u8		TIM4CH1_CAPTURE_STA;		    				
// extern u16	TIM4CH1_CAPTURE_VAL;



#endif



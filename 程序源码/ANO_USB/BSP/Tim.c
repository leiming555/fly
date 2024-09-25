#include "tim.h"

/**************************实现函数********************************************
*函数原型:		
*功　　能:1ms中断一次,计数器为1000		
*******************************************************************************/
void Tim3_Init(u16 period_num)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_DeInit(TIM3);

	TIM_TimeBaseStructure.TIM_Period=period_num;//装载值
	//prescaler is 1200,that is 72000000/72/500=2000Hz;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//分频系数
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//clear the TIM2 overflow interrupt flag
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//TIM2 overflow interrupt enable
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//enable TIM2
	TIM_Cmd(TIM3,ENABLE);
}
/**************************实现函数********************************************
*函数原型:		
*功　　能:用于捕捉PPM,使用PA0
*******************************************************************************/
void Tim2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
/////////////////////////////////////////////////////////////////////////////////////
//GPIO初始化	
   /* GPIOD Periph clock enable */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   
  /* TIM2 channel 1 pin (PA.0) configuration */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
/////////////////////////////////////////////////////////////////////////////////////	
//分频初始化	
	TIM_DeInit(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//装载值
	//CLK = 72000000/TIM_Prescaler
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//分频系数
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
/////////////////////////////////////////////////////////////////////////////////////	
//捕捉初始化
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿触发
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//通道方向选择
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;     //每次检测到输入捕捉就出发一次捕捉
  TIM_ICInitStructure.TIM_ICFilter = 0x0;       //滤波设置  0~F

  TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
  /* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);
   /* Enable the CC1 Interrupt Request */
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
}		


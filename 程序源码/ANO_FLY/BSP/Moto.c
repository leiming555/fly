#include "moto.h"

int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
int16_t MOTO3_PWM = 0;
int16_t MOTO4_PWM = 0;

void Moto_PwmRflash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{		
	if(MOTO1_PWM>Moto_PwmMax)	MOTO1_PWM = Moto_PwmMax;
	if(MOTO2_PWM>Moto_PwmMax)	MOTO2_PWM = Moto_PwmMax;
	if(MOTO3_PWM>Moto_PwmMax)	MOTO3_PWM = Moto_PwmMax;
	if(MOTO4_PWM>Moto_PwmMax)	MOTO4_PWM = Moto_PwmMax;
	if(MOTO1_PWM<0)	MOTO1_PWM = 0;
	if(MOTO2_PWM<0)	MOTO2_PWM = 0;
	if(MOTO3_PWM<0)	MOTO3_PWM = 0;
	if(MOTO4_PWM<0)	MOTO4_PWM = 0;
	

	TIM2->CCR1 = MOTO1_PWM; //
	TIM2->CCR2 = MOTO2_PWM;
	TIM8->CCR1 = MOTO3_PWM; //
	TIM8->CCR2 = MOTO4_PWM;
}
static TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure,TIM8_TimeBaseStructure;
static TIM_OCInitTypeDef TIM2_OCInitStructure,TIM8_OCInitStructure;

void Tim2_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
		TIM_DeInit(TIM2);												 //复位定时器8所有寄存器

    /* Time Base configuration */
    TIM2_TimeBaseStructure.TIM_Prescaler = 35;				 //预分频数为0,不分频
    TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //计娄方式为顺序计数模式，增大型
    TIM2_TimeBaseStructure.TIM_Period = 1000-1;					 //设置计数器溢出后的重载初值
    TIM2_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //配置时钟分隔值
    TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //循环计数次数值

    TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);				     //用以上参数初始化定时器时间基础模块
  
    /* Channel 1 Configuration in PWM mode */
    TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //输出方式为PWM模式1
 
    TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能输出比较状态
    TIM2_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能定时器互补输出               
    //TIM2_OCInitStructure.TIM_Pulse = 2000; 						 //设置脉宽
    TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //输出比较极性为高
    TIM2_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //打开空闲状态选择关闭
	
	TIM_OC1Init(TIM2,&TIM2_OCInitStructure); 		         //用以上参数初始化TIM8的通道1
	TIM_OC2Init(TIM2,&TIM2_OCInitStructure); 		         //用以上参数初始化TIM8的通道2

    TIM_Cmd(TIM2,ENABLE);							   				 //使能定时器8
    TIM_CtrlPWMOutputs(TIM2,ENABLE);				   				 //使能定时器8的PWM输出	 频率 
}

void Tim8_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		TIM_DeInit(TIM8);												 //复位定时器8所有寄存器
    /* Time Base configuration */
    TIM8_TimeBaseStructure.TIM_Prescaler = 35;				 //预分频数为0,不分频
    TIM8_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //计娄方式为顺序计数模式，增大型
    TIM8_TimeBaseStructure.TIM_Period = 1000-1;					 //设置计数器溢出后的重载初值
    TIM8_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //配置时钟分隔值
    TIM8_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //循环计数次数值

    TIM_TimeBaseInit(TIM8,&TIM8_TimeBaseStructure);				     //用以上参数初始化定时器时间基础模块

    /* Channel 1 Configuration in PWM mode */
    TIM8_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //输出方式为PWM模式1
 
    TIM8_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能输出比较状态
    TIM8_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能定时器互补输出               
   // TIM8_OCInitStructure.TIM_Pulse =2000; 						 							//设置脉宽
    TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //输出比较极性为高
    TIM8_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //打开空闲状态选择关闭
	
		TIM_OC1Init(TIM8,&TIM8_OCInitStructure); 		         //用以上参数初始化TIM8的通道1
		TIM_OC2Init(TIM8,&TIM8_OCInitStructure); 		         //用以上参数初始化TIM8的通道2

    TIM_Cmd(TIM8,ENABLE);							   				 //使能定时器8
    TIM_CtrlPWMOutputs(TIM8,ENABLE);				   	 //使能定时器8的PWM输出	 频率
}

void Moto_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//使能电机用的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	
	//设置电机使用到得管脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;// | GPIO_Pin_2 | GPIO_Pin_3 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	Tim2_init();
	Tim8_init();
}


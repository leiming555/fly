//#include "TIMER.h"
#include "TIMCap.h"
#include "stm32f10x.h"
#include "app/rc/rc.h"

static u16 TIM1_Prescaler,TIM2_Prescaler,TIM3_Prescaler,TIM4_Prescaler,TIM5_Prescaler,TIM8_Prescaler;

u16 frequency0, percent0;
u16 frequency1, percent1;
u16 frequency2, percent2;
u16 frequency3, percent3;
u16 frequency4, percent4;

void TIM1_BRK_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Break) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Break); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update); //清除中断标志位	    
//	 	printf("\r\n TIM1");
	}
}
void TIM1_TRG_COM_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Trigger) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Trigger); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM1_CC_IRQHandler(void)
{
	//printf("TIM1\r\n");
	TIM1_CO1_Check(&frequency4,&percent4);
	//TIM1_CO2_Check(&frequency1,&percent1);
	//TIM1_CO3_Check(&frequency2,&percent2);
	//TIM1_CO4_Check(&frequency3,&percent3);
}
extern void NRF_Send_RC(void);
////定时器2中断服务程序	 
void TIM2_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位	    
	  //printf("\r\n TIM2");
	}
	TIM2_CO1_Check(&frequency0,&percent0);
	TIM2_CO2_Check(&frequency1,&percent1);
	TIM2_CO3_Check(&frequency2,&percent2);
	TIM2_CO4_Check(&frequency3,&percent3);
}
//extern u16 times;
////定时器3中断服务程序	 
//void TIM3_IRQHandler(void)
//{ 
//		  
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)		 
//	{
//		 TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位	    
////	   printf(" %d \r\n",times);
//		 times=0;
//		 
//	}			     	    					    	    
//}
//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清除中断标志位	    
//	  printf("\r\n TIM4");
	}
		     	    					    	    
}
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)		 
	{	    
	 	TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //清除中断标志位
	}
	TIM5_CO1_Check(&frequency0,&percent0);
	TIM5_CO2_Check(&frequency1,&percent1);
	TIM5_CO3_Check(&frequency2,&percent2);
	TIM5_CO4_Check(&frequency3,&percent3);		     	    					    
}
//定时器6中断服务程序	 
void TIM6_IRQHandler(void)
{ 		  
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update); //清除中断标志位	    
//	 	printf("\r\n TIM6");
	}			     	    					    	    
}
//定时器7中断服务程序	 
void TIM7_IRQHandler(void)
{ 		  
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update); //清除中断标志位
//		printf("\r\n TIM7");	    	 
	}			     	    					    	    
}
//定时器8中断服务程序
void TIM8_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update); //清除中断标志位	    
//	 	printf("\r\n TIM8");
	}
}	 
void TIM8_CC_IRQHandler(void)
{ 	
	//printf("TIM8_In \r\n");
	TIM8_CO1_Check(&frequency0,&percent0);
	TIM8_CO2_Check(&frequency1,&percent1);
	TIM8_CO3_Check(&frequency2,&percent2);
	TIM8_CO4_Check(&frequency3,&percent3);			     	    					    	    
}
void TIM8_TRG_COM_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Trigger) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Trigger); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM8_BRK_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Break) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Break); 	    
	 	//printf("\r\n TIM8");
	}
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM1_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//启动AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//启动TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM1_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO端口的第1位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //IO端口的第2位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //IO端口的第3位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//初始化定时器1 TIM1	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	if(OC==1)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM1_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
    //TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
    //TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	if(OC==1)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM1,ENABLE ); 	//使能定时器5
}
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM1_CO1_Check(u16 *frequency,u16 *percent)		// PA8
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM1_Prescaler/All_Val);
				*percent=Up_Val;//*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM1)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM1_CO2_Check(u16 *frequency,u16 *percent)		// PA9
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM1)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM1_CO3_Check(u16 *frequency,u16 *percent)		// PA10
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM1)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM1_CO4_Check(u16 *frequency,u16 *percent)		// PA11
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM1)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM2_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM2_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	TIM2_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  //IO端口的第6位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 //PA0 下拉
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO端口的第1位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //IO端口的第2位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //IO端口的第3位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//初始化定时器2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	if(OC==1)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM2,ENABLE ); 	//使能定时器5
}
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM2_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM2_Prescaler/All_Val);
				*percent=Up_Val;//*10000L / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM2)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM2_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // 频率
				*percent=Up_Val;//*10000L / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM2)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM2_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // 频率
				*percent=Up_Val;//*10000L / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM2)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM2_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // 频率
				*percent=Up_Val;//*10000L / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM2)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM3_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM3_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOA时钟

	TIM3_Prescaler=Prescaler;//TIM3_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO端口的第6位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);						 //PA6 下拉
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO端口的第7位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)   //PB0
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO端口的第8位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	
	//初始化定时器3 TIM3	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	if(OC==1)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM3,ENABLE ); 	//使能定时器5
}
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM3_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM3_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM3)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM3_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM3)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM3_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM3)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM3_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM3)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM4_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM4_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOA时钟

	TIM4_Prescaler=Prescaler;//TIM4_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO端口的第6位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);						 //PB6 下拉
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO端口的第7位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO端口的第8位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO端口的第8位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	
	//初始化定时器4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	if(OC==1)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM4,ENABLE ); 	//使能定时器5
}
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM4_CO1_Check(u16 *frequency,u16 *percent)		// PB6
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM4_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM4)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM4_CO2_Check(u16 *frequency,u16 *percent)		// PB7
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM4)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM4_CO3_Check(u16 *frequency,u16 *percent)		// PB8
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM4)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM4_CO4_Check(u16 *frequency,u16 *percent)		// PB9
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM4)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM5_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	TIM5_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  //IO端口的第6位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 //PA0 下拉
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO端口的第1位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //IO端口的第2位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //IO端口的第3位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	if(OC==1)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
} 
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM5_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM5_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM5)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM5_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM5)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM5_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM5)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM5_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM5)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM8_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM8_ICInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);

	TIM8_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO端口的第6位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);						 //PC6 下拉
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO端口的第7位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO端口的第8位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO端口的第8位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	
	//初始化定时器8 TIM8	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM8输入捕获参数
	if(OC==1)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	选择输入端 IC1映射到TI1上
	else  if(OC==2)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM8_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //上升沿捕获
  	TIM8_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM8_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM8_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM8, &TIM8_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
    TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
    TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);
	
	if(OC==1)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
	else if(OC==2)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	

   	TIM_Cmd(TIM8,ENABLE ); 	//使能定时器5
} 
/*  用于规律  PWM  波的 频率 和 脉宽  检测   */
u8 	TIM8_CO1_Check(u16 *frequency,u16 *percent)		// PC6
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//标记捕获到了上升沿
			Bas_Val=TIM_GetCapture1(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM8_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM8)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM8_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC2) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC2);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture2(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM8)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
} 
u8 	TIM8_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC3) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture3(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM8)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}
u8 	TIM8_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC4) != RESET)               //捕获2发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC4);                  //清除中断标志位
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //标记捕获到了上升沿
			Bas_Val=TIM_GetCapture4(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // 两次上升沿的时间差 也就是一个周期的时间
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // 频率
				*percent=Up_Val*1000 / All_Val;	                  // 放大一百倍，也就是小数点后面两位
			}
			Last_Bas_Val=Bas_Val;				                  // 更新基准时间
	   		TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 设置为下降沿捕�

			return 1;
		}
		else if(OC_STA==1)		                                  //捕获到一个下降沿 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM8)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 设置为上升沿捕获
		}
		else {OC_STA=0;}			                              //清空				    
	}
	return 0 ;
}






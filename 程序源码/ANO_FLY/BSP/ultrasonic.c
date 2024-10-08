#include "ultrasonic.h"
//#include "delay.h"
#include "app/uart/uart1.h"
#include "stdio.h"

//#define Ultrasonic_Cap_TIM1 4
//#define Ultrasonic_Cap_TIM4 0
//#define Ultrasonic_Cap_TIM5 0

////extern void TIM1_Ultrasonic_Cap_Init(u16 arr, u16 psc);
////extern void TIM4_Ultrasonic_Cap_Init(u16 arr, u16 psc);
////extern void TIM5_Ultrasonic_Cap_Init(u16 arr, u16 psc);

////static void TIM_GPIO_Init(void)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    RCC_APB2PeriphClockCmd(RCC_ULTRASONIC_ECHO, ENABLE);  //使能GPIOA时钟

////    GPIO_InitStructure.GPIO_Pin   = ULTRASONIC_ECHO_PIN;  //PX.x 清除之前设置
////    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;        //PX.x 输入
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
////    GPIO_Init(ULTRASONIC_ECHO_GPIO, &GPIO_InitStructure);
////    GPIO_ResetBits(ULTRASONIC_ECHO_GPIO, ULTRASONIC_ECHO_PIN);//PX.x 下拉
////}
//void Ultrasonic_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_ULTRASONIC_TRIG, ENABLE); //使能Px端口时钟
//    GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG_PIN;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(ULTRASONIC_TRIG_GPIO, &GPIO_InitStructure);
//#if   Ultrasonic_Cap_TIM1
//    TIM1_Ultrasonic_Cap_Init(0XFFFF, 72 - 1);
//#elif Ultrasonic_Cap_TIM4
//    TIM4_Ultrasonic_Cap_Init(0XFFFF, 72 - 1);
//#elif Ultrasonic_Cap_TIM5
//    TIM5_Ultrasonic_Cap_Init(0XFFFF, 72 - 1);
//#endif
//}

//#if   Ultrasonic_Cap_TIM1
//void TIM1_Ultrasonic_Cap_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    NVIC_InitTypeDef        NVIC_InitStructure;
//    TIM_ICInitTypeDef       TIM1_ICInitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //使能TIM5时钟
//    TIM_GPIO_Init();

//    //初始化定时器1 TIM1
//    TIM_TimeBaseStructure.TIM_Period    = arr;  //设定计数器自动重装值
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;  //预分频器
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//    //初始化TIM5输入捕获参数
//#if   Ultrasonic_Cap_TIM1==1
//    TIM1_ICInitStructure.TIM_Channel        = TIM_Channel_1;           //CC1S=01     选择输入端 IC1映射到TI1上
//#elif   Ultrasonic_Cap_TIM1==2
//    TIM1_ICInitStructure.TIM_Channel        = TIM_Channel_2;           //CC1S=01     选择输入端 IC1映射到TI1上
//#elif   Ultrasonic_Cap_TIM1==3
//    TIM1_ICInitStructure.TIM_Channel        = TIM_Channel_3;           //CC1S=01     选择输入端 IC1映射到TI1上
//#elif   Ultrasonic_Cap_TIM1==4
//    TIM1_ICInitStructure.TIM_Channel        = TIM_Channel_4;           //CC1S=01     选择输入端 IC1映射到TI1上
//#endif
//    TIM1_ICInitStructure.TIM_ICPolarity     = TIM_ICPolarity_Rising;   //上升沿捕获
//    TIM1_ICInitStructure.TIM_ICSelection    = TIM_ICSelection_DirectTI;//映射到TI1上
//    TIM1_ICInitStructure.TIM_ICPrescaler    = TIM_ICPSC_DIV1;          //配置输入分频,不分频
//    TIM1_ICInitStructure.TIM_ICFilter = 0x00;                          //IC1F=0000 配置输入滤波器 不滤波
//    TIM_ICInit(TIM1, &TIM1_ICInitStructure);

//    //中断分组初始化
//    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;           //TIMx中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //从优先级0级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
//    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//    TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_CC4, ENABLE);   //允许更新中断 ,允许CC1IE捕获中断

//    TIM_Cmd(TIM1, ENABLE ); //使能定时器5
//}

//u8  TIM1CHx_CAPTURE_STA = 0;//输入捕获状态
//u16 TIM1CHx_CAPTURE_VAL;    //输入捕获值
////定时器1中断服务程序
//void TIM1_CC_IRQHandler(void)
//{
//    if ((TIM1CHx_CAPTURE_STA & 0X80) == 0) //还未成功捕获
//    {
//#if   Ultrasonic_Cap_TIM1==1
//#define TIM_IT_CCx TIM_IT_CC1
//#define TIM_GetCapturex TIM_GetCapture1
//#define TIM_OCxPolarityConfig TIM_OC1PolarityConfig
//#elif   Ultrasonic_Cap_TIM1==2
//#define TIM_IT_CCx TIM_IT_CC2
//#define TIM_GetCapturex TIM_GetCapture2
//#define TIM_OCxPolarityConfig TIM_OC2PolarityConfig
//#elif   Ultrasonic_Cap_TIM1==3
//#define TIM_IT_CCx TIM_IT_CC3
//#define TIM_GetCapturex TIM_GetCapture3
//#define TIM_OCxPolarityConfig TIM_OC1PolarityConfig
//#elif   Ultrasonic_Cap_TIM1==4
//#define TIM_IT_CCx TIM_IT_CC4
//#define TIM_GetCapturex TIM_GetCapture4
//#define TIM_OCxPolarityConfig TIM_OC4PolarityConfig
//#endif
//        if (TIM_GetITStatus(TIM1, TIM_IT_CCx) != RESET)//捕获1发生捕获事件
//        {
//            if (TIM1CHx_CAPTURE_STA & 0X40)     //捕获到一个下降沿
//            {
//                TIM1CHx_CAPTURE_STA |= 0X80;    //标记成功捕获到一次上升沿
//                TIM1CHx_CAPTURE_VAL = TIM_GetCapturex(TIM1);
//                //注意！！！
//                TIM_OCxPolarityConfig(TIM1, TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//            }
//            else                                //还未开始,第一次捕获上升沿
//            {
//                TIM1CHx_CAPTURE_STA = 0;        //清空
//                TIM1CHx_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM1, 0);
//                TIM1CHx_CAPTURE_STA |= 0X40;    //标记捕获到了上升沿
//                //注意！！！
//                TIM_OCxPolarityConfig(TIM1, TIM_ICPolarity_Falling);    //CC1P=1 设置为下降沿捕获
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM1, TIM_IT_CCx); //清除中断标志位

//}
//void TIM1_UP_IRQHandler(void)
//{
//    if ((TIM1CHx_CAPTURE_STA & 0X80) == 0) //还未成功捕获
//    {
//        if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
//        {
//            if (TIM1CHx_CAPTURE_STA & 0X40) //已经捕获到高电平了
//            {
//                if ((TIM1CHx_CAPTURE_STA & 0X3F) == 0X3F) //高电平太长了
//                {
//                    TIM1CHx_CAPTURE_STA |= 0X80; //标记成功捕获了一次
//                    TIM1CHx_CAPTURE_VAL = 0XFFFF;
//                }
//                else TIM1CHx_CAPTURE_STA++;
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM1, TIM_IT_Update); //清除中断标志位
//}

//void Ultrasonic_TRIG (void)
//{
//    TRIG_H;
//    TIM1CHx_CAPTURE_STA = 0; //开启下一次捕获
//    int j = 720;
//    while (j--) {}; //delay_us(10);
//    TRIG_L;
//}

//u32 Ultrasonic_ECHO (void)
//{
//    u32 temp = 0;
//    char senf_buf[100];
//    if (TIM1CHx_CAPTURE_STA & 0X80) //成功捕获到了一次上升沿
//    {
//        temp = TIM1CHx_CAPTURE_STA & 0X3F;
//        temp *= 65536;//溢出时间总和
//        temp += TIM1CHx_CAPTURE_VAL; //得到总的高电平时间
//        sprintf(senf_buf, "TIME:%dms %dus %dM%dMM\r\n", temp / 1000, temp % 1000, (temp * 340 / 1000 / 2) / 1000, (temp * 340 / 1000 / 2) % 1000);//打印总的高点平时间
//        //Uart1_Put_String(senf_buf);
//				//TIM1CHx_CAPTURE_STA=0;
//    }
//    return (temp * 340 / 1000 / 2);
//}


//#elif Ultrasonic_Cap_TIM4
//void TIM4_Ultrasonic_Cap_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    NVIC_InitTypeDef                NVIC_InitStructure;
//    TIM_ICInitTypeDef           TIM4_ICInitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //使能TIM5时钟

//    TIM_GPIO_Init();

//    //初始化定时器5 TIM5
//    TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;  //预分频器
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//    //初始化TIM5输入捕获参数
//    TIM4_ICInitStructure.TIM_Channel            = TIM_Channel_3; //CC1S=01     选择输入端 IC1映射到TI1上
//    TIM4_ICInitStructure.TIM_ICPolarity     = TIM_ICPolarity_Rising;        //上升沿捕获
//    TIM4_ICInitStructure.TIM_ICSelection    = TIM_ICSelection_DirectTI;     //映射到TI1上
//    TIM4_ICInitStructure.TIM_ICPrescaler    = TIM_ICPSC_DIV1;                       //配置输入分频,不分频
//    TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
//    TIM_ICInit(TIM4, &TIM4_ICInitStructure);

//    //中断分组初始化
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     //TIM3中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
//    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//    TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

//    TIM_Cmd(TIM4, ENABLE ); //使能定时器5
//}
//u8  TIM4CH1_CAPTURE_STA = 0;//输入捕获状态
//u16 TIM4CH1_CAPTURE_VAL;    //输入捕获值
////定时器4中断服务程序
//void TIM4_IRQHandler(void)
//{
//    if ((TIM4CH1_CAPTURE_STA & 0X80) == 0) //还未成功捕获
//    {
//        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
//        {
//            if (TIM4CH1_CAPTURE_STA & 0X40) //已经捕获到高电平了
//            {
//                if ((TIM4CH1_CAPTURE_STA & 0X3F) == 0X3F) //高电平太长了
//                {
//                    TIM4CH1_CAPTURE_STA |= 0X80; //标记成功捕获了一次
//                    TIM4CH1_CAPTURE_VAL = 0XFFFF;
//                }
//                else TIM4CH1_CAPTURE_STA++;
//            }
//        }
//        if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
//        {
//            if (TIM4CH1_CAPTURE_STA & 0X40)     //捕获到一个下降沿
//            {
//                TIM4CH1_CAPTURE_STA |= 0X80;    //标记成功捕获到一次上升沿
//                TIM4CH1_CAPTURE_VAL = TIM_GetCapture3(TIM4);
//                //注意！！！
//                TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//            }
//            else                                //还未开始,第一次捕获上升沿
//            {
//                TIM4CH1_CAPTURE_STA = 0;        //清空
//                TIM4CH1_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM4, 0);
//                TIM4CH1_CAPTURE_STA |= 0X40;    //标记捕获到了上升沿
//                //注意！！！
//                TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Falling);    //CC1P=1 设置为下降沿捕获
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3 | TIM_IT_Update); //清除中断标志位
//}
//u32 ultrasonic (void)
//{
//    u32 temp = 0;
//    TRIG_H;
//    TIM4CH1_CAPTURE_STA = 0; //开启下一次捕获
//    int j = 720;
//    while (j--);
//    //delay_us(10);
//    TRIG_L;
//    while (1)
//    {
//        if (TIM4CH1_CAPTURE_STA & 0X80) //成功捕获到了一次上升沿
//        {
//            temp = TIM4CH1_CAPTURE_STA & 0X3F;
//            temp *= 65536;//溢出时间总和
//            temp += TIM4CH1_CAPTURE_VAL; //得到总的高电平时间
//            //USART_OUT(USART1, "TIME:%dms %dus %dM%dMM\r\n", temp/1000,temp%1000,(temp*340/1000/2)/1000,(temp*340/1000/2)%1000); //打印总的高点平时间
//            break;
//        }
//    }
//    return (temp * 340 / 1000 / 2);
//}
//#elif Ultrasonic_Cap_TIM5
//void TIM5_Ultrasonic_Cap_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    TIM_ICInitTypeDef  TIM5_ICInitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   //使能TIM5时钟

//    TIM_GPIO_Init();

//    //初始化定时器5 TIM5
//    TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;  //预分频器
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//    //初始化TIM5输入捕获参数
//    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01     选择输入端 IC1映射到TI1上
//    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
//    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
//    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
//    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
//    TIM_ICInit(TIM5, &TIM5_ICInitStructure);

//    //中断分组初始化
//    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                     //TIM3中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
//    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//    TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

//    TIM_Cmd(TIM5, ENABLE ); //使能定时器5
//}

//u8  TIM5CH1_CAPTURE_STA = 0;//输入捕获状态
//u16 TIM5CH1_CAPTURE_VAL;    //输入捕获值
////定时器4中断服务程序
//void TIM5_IRQHandler(void)
//{
//    if ((TIM5CH1_CAPTURE_STA & 0X80) == 0) //还未成功捕获
//    {
//        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
//        {
//            if (TIM5CH1_CAPTURE_STA & 0X40) //已经捕获到高电平了
//            {
//                if ((TIM5CH1_CAPTURE_STA & 0X3F) == 0X3F) //高电平太长了
//                {
//                    TIM5CH1_CAPTURE_STA |= 0X80; //标记成功捕获了一次
//                    TIM5CH1_CAPTURE_VAL = 0XFFFF;
//                }
//                else TIM5CH1_CAPTURE_STA++;
//            }
//        }
//        if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
//        {
//            if (TIM5CH1_CAPTURE_STA & 0X40)     //捕获到一个下降沿
//            {
//                TIM5CH1_CAPTURE_STA |= 0X80;    //标记成功捕获到一次上升沿
//                TIM5CH1_CAPTURE_VAL = TIM_GetCapture3(TIM5);
//                //注意！！！
//                TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//            }
//            else                                //还未开始,第一次捕获上升沿
//            {
//                TIM5CH1_CAPTURE_STA = 0;        //清空
//                TIM5CH1_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM5, 0);
//                TIM5CH1_CAPTURE_STA |= 0X40;    //标记捕获到了上升沿
//                //注意！！！
//                TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Falling);    //CC1P=1 设置为下降沿捕获
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3 | TIM_IT_Update); //清除中断标志位
////}
//#endif



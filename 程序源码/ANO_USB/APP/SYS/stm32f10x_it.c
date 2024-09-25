/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp/bsp.h"
#include "app/uart/uart1.h"
#include "app/rc/rc.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
/*=====================================================================================================*/
/*=====================================================================================================*/
void USART1_IRQHandler(void)  //串口中断函数
{
    Uart1_IRQ();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
//void TIM2_IRQHandler(void)
//{
//    static u8   RC_Ch = 0;
//    static u16  RC_Value[10];

//    if (TIM2->SR & TIM_IT_CC1) //if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)
//    {
//        u16 CC1_Value_Now = TIM2->CCR1;//读ccr,清cc1if标志
//        TIM2->CNT = 0;                 //清cnt
//        if (CC1_Value_Now > 3000)     //判断同步信号
//            RC_Ch = 0;
//        RC_Value[RC_Ch] = CC1_Value_Now;
//        RC_Ch++;
//        if (RC_Ch == 1)
//        {
//            Rc_Get.THROTTLE = RC_Value[3];//节流阀
//            Rc_Get.YAW      = RC_Value[4];//偏航
//            Rc_Get.ROLL     = RC_Value[1];//翻滚
//            Rc_Get.PITCH    = RC_Value[2];//倾斜
//            Rc_Get.AUX1 = RC_Value[5];
//            Rc_Get.AUX2 = RC_Value[6];
//            Rc_Get.AUX3 = RC_Value[7];
//            Rc_Get.AUX4 = RC_Value[8];
//            Rc_Get.AUX5 = RC_Value[9];
//            //Uart1_Send_RCdata();
//            NRF_Send_RC();
//        }
//    }
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
extern u16 percent0;
extern u16 percent1;
extern u16 percent2;
extern u16 percent3;
void TIM3_IRQHandler(void)      //0.5ms中断一次
{
    static u8 ms1 = 0, ms2 = 0, ms5 = 0, ms10 = 0;          //中断次数计数器
    if (TIM3->SR & TIM_IT_Update)       //if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
    {
        TIM3->SR = ~TIM_FLAG_Update;//TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);   //清除中断标志
        if (!SYS_INIT_OK)
            return;
        //每次中断都执行,0.5ms
        ms1++;
        ms2++;
        ms5++;
        ms10++;
        //Nrf_Check_Event();
        if (ms1 == 2)           //每两次中断执行一次,1ms
        {
            ms1 = 0;
        }
        if (ms2 == 4)           //每四次中断执行一次,2ms
        {
            ms2 = 0;
						Rc_Get.THROTTLE = percent2-200;//节流阀
						Rc_Get.YAW      = percent3;//偏航
						Rc_Get.ROLL     = 3000-percent0;//翻滚
						Rc_Get.PITCH    = percent1;//倾斜
						Rc_Get.AUX1 = 1000;
						Rc_Get.AUX2 = 1000;
						Rc_Get.AUX3 = 1000;
						Rc_Get.AUX4 = 1000;
						Rc_Get.AUX5 = 1000;
						//sprintf((char*)str,"\r\n %d,%d,%d,%d",percent0,percent1,percent2,percent3);
						//Uart1_Put_String(str);		
						NRF_Send_RC();

        }
        if (ms5 == 10)
        {
            ms5 = 0;                //每十次中断执行一次,5ms
        }
        if (ms10 == 20)
        {
            ms10 = 0;               //没二十次中断执行一次,10ms
        }

    }
}

/*=====================================================================================================*/
/*=====================================================================================================*/
// void EXTI1_IRQHandler(void)
// {
//  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
//  {
//      EXTI_ClearITPendingBit(EXTI_Line1);
//  }
// }
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "BSP/BSP.H"
#include "app/uart/uart1.h"
#include "app/rc/rc.h"
#include "TIMCap.h"
#include "stdio.h"

//#define CLI()      __set_PRIMASK(1)  
//#define SEI()      __set_PRIMASK(0)

////////////////////////////////////////////////////////////////////////////////
void SYS_INIT(void)
{
	Tim3_Init(500);				//1000=1MS,500=0.5MS
	//Tim2_Init();					//用于捕捉PPM
	TIM2_Cap_Init(72,65535,1);
	TIM2_Cap_Init(72,65535,2);
	TIM2_Cap_Init(72,65535,3);
	TIM2_Cap_Init(72,65535,4);
	Nvic_Init();					//中断初始化
	Uart1_Init(500000);
	Spi2_Init();
	Nrf24l01_Init(MODEL_RX2,40);
	if(Nrf24l01_Check())Uart1_Put_String("NRF24L01 IS OK !\r\n");
	else Uart1_Put_String("NRF24L01 IS NOT OK !\r\n");
}

u8 str[100];
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	SYS_INIT_OK=0;
	SYS_INIT();
	SYS_INIT_OK=1;
	while (1)
	{			     
		Uart_CheckEvent();
		Nrf_Check_Event();
		if(NRF_SEND_RC_FLAG)
		{
			NRF_SEND_RC_FLAG = 0;
			NRF_TxPacket_AP(NRF24L01_TXDATA_RC,32);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "BSP/BSP.H"
#include "app/uart/uart1.h"
#include "app/rc/rc.h"
#include "BSP/ultrasonic.H"
#include "bsp/tim.h"

//#include "STM32_I2C.h"
/*
TIM3
TIM1
*/

extern void i2cInit(void);

//#define CLI()      __set_PRIMASK(1)  
//#define SEI()      __set_PRIMASK(0)
////////////////////////////////////////////////////////////////////////////////
//extern void Tim7_Init(u16 period_num);//用于精确延时

void SYS_INIT(void)
{
	//MCO_INIT();			//时钟输出初始化 2.4G 时钟
	//LED_INIT();			//LED初始化
	//LED_FLASH();		//LED闪亮
	Tim3_Init(500);	//1000=1MS,500=0.5MS
	//Tim7_Init(500);	//1000=1MS,500=0.5MS
	
	Moto_Init();		//电机初始化
	//Uart1_Init(500000);
	Spi2_Init();
	Nvic_Init();		//中断初始化
	Nrf24l01_Init(MODEL_TX2,40);
 	if(Nrf24l01_Check())	Uart1_Put_String("FLY_NRF24L01 IS OK !\r\n");
 	else 									Uart1_Put_String("FLY_NRF24L01 IS NOT OK !\r\n");

	i2cInit();			//I2c初始化
	MPU6050_Init();
	//Ultrasonic_Init();

	ADC1_Init();//电压检测初始化
	FLASH_Unlock();//模拟EEROM初始化
	EE_INIT();
	EE_READ_ACC_OFFSET();
	EE_READ_GYRO_OFFSET();
	EE_READ_PID();
}
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	SYS_INIT_OK=0;
	SYS_INIT();
	SYS_INIT_OK=1;
	while (1)
	{			     
		
	}
}
////////////////////////////////////////////////////////////////////////////////


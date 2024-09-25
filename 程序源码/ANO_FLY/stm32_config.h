#ifndef __STM32_CONFIG_
#define __STM32_CONFIG_
//#include "stm32_config.h"

///***I2C CONGIG ***/
//#define RCC_I2C_SCL RCC_APB2Periph_GPIOD
//#define I2C_SCL_GPIO GPIOD
//#define I2C_SCL_PIN GPIO_Pin_6

//#define RCC_I2C_SDA RCC_APB2Periph_GPIOD
//#define I2C_SDA_GPIO GPIOD
//#define I2C_SDA_PIN GPIO_Pin_3
///***I2C CONGIG ***/

///***HMC5883L   I2c ***/
//#define Single_Write I2c_Write
//#define Delayms delay_ms
///***HMC5883L***/

/***Ultrasonic***/
//启动 检测
//#define RCC_ULTRASONIC_TRIG RCC_APB2Periph_GPIOA
//#define ULTRASONIC_TRIG_GPIO    GPIOA
//#define ULTRASONIC_TRIG_PIN     GPIO_Pin_8
////返回 信号
//#define RCC_ULTRASONIC_ECHO RCC_APB2Periph_GPIOA
//#define ULTRASONIC_ECHO_GPIO    GPIOA
//#define ULTRASONIC_ECHO_PIN     GPIO_Pin_11
/***Ultrasonic***/

///***USART***/
//#define DEBUG_USART USART1

//#define EN_USART_           1       //使能（1）/禁止（0）串口1
//#define EN_USART2_          1       //使能（1）/禁止（0）串口2
//#define EN_USART3_          0       //使能（1）/禁止（0）串口3
///***USART***/

///*** LCD ***/
////RST
//#define RCC_LCD_RST 	  RCC_APB2Periph_GPIOD
//#define LCD_RST_GPIO   	GPIOD
//#define LCD_RST_Pin 	  GPIO_Pin_12
////LIGHT
//#define RCC_LCD_LIGHT 	RCC_APB2Periph_GPIOC
//#define LCD_LIGHT_GPIO 	GPIOC
//#define LCD_LIGHT_Pin 	GPIO_Pin_0
////RD
//#define RCC_LCD_RD	RCC_APB2Periph_GPIOD
//#define LCD_RD_GPIO GPIOD
//#define LCD_RD_Pin 	GPIO_Pin_4
////WR
//#define RCC_LCD_WR	RCC_APB2Periph_GPIOD
//#define LCD_WR_GPIO GPIOD
//#define LCD_WR_Pin 	GPIO_Pin_5
////CS
//#define RCC_LCD_CS	RCC_APB2Periph_GPIOD
//#define LCD_CS_GPIO GPIOD
//#define LCD_CS_Pin 	GPIO_Pin_7
////RS
//#define RCC_LCD_RS	RCC_APB2Periph_GPIOD
//#define LCD_RS_GPIO GPIOD
//#define LCD_RS_Pin 	GPIO_Pin_11
///*** LCD ***/
///***TOUCH***/
////#define LCD_TOUCH_SPI_SOFT

//#define RCC_LCD_TOUCH_PEN	RCC_APB2Periph_GPIOA
//#define LCD_TOUCH_PEN_GPIO GPIOA
//#define LCD_TOUCH_PEN_Pin  GPIO_Pin_4

//#define RCC_LCD_TOUCH_TCS	RCC_APB2Periph_GPIOC
//#define LCD_TOUCH_TCS_GPIO GPIOC
//#define LCD_TOUCH_TCS_Pin 	GPIO_Pin_4

///***TOUCH***/

///***MPU6050***/
//#define MPU6050_USE_DMP
///***MPU6050***/

#endif


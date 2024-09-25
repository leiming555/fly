#ifndef __STM32_I2C_H
#define __STM32_I2C_H
//#include "define.h"
#include "stm32f10x.h"

/***I2C CONGIG ***/
#define RCC_I2C_SCL RCC_APB2Periph_GPIOC
#define I2C_SCL_GPIO GPIOC
#define I2C_SCL_PIN GPIO_Pin_9

#define RCC_I2C_SDA RCC_APB2Periph_GPIOC
#define I2C_SDA_GPIO GPIOC
#define I2C_SDA_PIN GPIO_Pin_8
/***I2C CONGIG ***/

/*====================================================================================================*/
/*====================================================================================================*/
//uint8_t ANO_Tech_I2C1_Write_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
//								//I2C写多字节，立即返回1
//uint8_t ANO_Tech_I2C1_Write_1Byte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData);
//								//I2C写单字节，写完后返回1
//uint8_t ANO_Tech_I2C1_Write_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
//								//I2C写多字节，写完后返回1
//uint8_t ANO_Tech_I2C1_Read_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
//								//I2C读单字节或多字节，立即返回1（返回时读取操作很可能还未完成）
//uint8_t ANO_Tech_I2C1_Read_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
#define bool uint8_t
#define false 0
#define true 1

#define ANO_Tech_I2C1_Write_Int i2cWriteBuffer
#define ANO_Tech_I2C1_Write_1Byte i2cWrite
#define ANO_Tech_I2C1_Write_Buf i2cWriteBuffer

#define ANO_Tech_I2C1_Read_Int i2cRead
#define ANO_Tech_I2C1_Read_Buf i2cRead

bool i2cWriteBuffer(uint8_t addr_, uint8_t reg_, uint8_t len_, uint8_t *data);
bool i2cWrite(uint8_t addr_, uint8_t reg_, uint8_t data);
bool i2cRead(uint8_t addr_, uint8_t reg_, uint8_t len, uint8_t* buf);
void i2cInit(void);
uint16_t i2cGetErrorCounter(void);
static void i2cUnstick(void);

/*====================================================================================================*/
/*====================================================================================================*/
#endif

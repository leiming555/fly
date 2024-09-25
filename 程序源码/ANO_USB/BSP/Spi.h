#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f10x.h"
//#define NRF24L01_SPI1

#ifdef NRF24L01_SPI1
#error
#define SPI_CE_H()   GPIO_SetBits(GPIOB, GPIO_Pin_0) 
#define SPI_CE_L()   GPIO_ResetBits(GPIOB, GPIO_Pin_0)

#define SPI_CSN_H()  GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define SPI_CSN_L()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

#else

#define NRF24l01_CE_RCC RCC_APB2Periph_GPIOB
#define NRF24l01_CE_GPIO GPIOB
#define NRF24l01_CE_PIN GPIO_Pin_11

#define NRF24l01_CSN_RCC RCC_APB2Periph_GPIOC
#define NRF24l01_CSN_GPIO GPIOC
#define NRF24l01_CSN_PIN GPIO_Pin_6

#define NRF24l01_IQR_RCC RCC_APB2Periph_GPIOC
#define NRF24l01_IQR_GPIO GPIOC
#define NRF24l01_IQR_PIN GPIO_Pin_7

#define SPI_CE_H()   GPIO_SetBits(NRF24l01_CE_GPIO, NRF24l01_CE_PIN) 
#define SPI_CE_L()   GPIO_ResetBits(NRF24l01_CE_GPIO, NRF24l01_CE_PIN)

#define SPI_CSN_H()  GPIO_SetBits(NRF24l01_CSN_GPIO, NRF24l01_CSN_PIN)
#define SPI_CSN_L()  GPIO_ResetBits(NRF24l01_CSN_GPIO, NRF24l01_CSN_PIN)

#endif

void Spi1_Init(void);
void Spi2_Init(void);
u8 Spi_RW(u8 dat);

#endif

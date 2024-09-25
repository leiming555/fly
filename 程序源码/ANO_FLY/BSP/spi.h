#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f10x.h"
//#define NRF24L01_SPI1
#ifdef NRF24L01_SPI1

#define SPI_CE_H()   GPIO_SetBits(GPIOA, GPIO_Pin_11) 
#define SPI_CE_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_11)

#define SPI_CSN_H()  GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define SPI_CSN_L()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

void Spi1_Init(void);
#else

#define NRF24l01_CE_RCC RCC_APB2Periph_GPIOD
#define NRF24l01_CE_GPIO GPIOD
#define NRF24l01_CE_PIN GPIO_Pin_13

#define NRF24l01_CSN_RCC RCC_APB2Periph_GPIOB
#define NRF24l01_CSN_GPIO GPIOB
#define NRF24l01_CSN_PIN GPIO_Pin_12

#define NRF24l01_IQR_RCC RCC_APB2Periph_GPIOD
#define NRF24l01_IQR_GPIO GPIOD
#define NRF24l01_IQR_PIN GPIO_Pin_12


#define SPI_CE_H()   GPIO_SetBits(NRF24l01_CE_GPIO, NRF24l01_CE_PIN) 
#define SPI_CE_L()   GPIO_ResetBits(NRF24l01_CE_GPIO, NRF24l01_CE_PIN)

#define SPI_CSN_H()  GPIO_SetBits(NRF24l01_CSN_GPIO, NRF24l01_CSN_PIN)
#define SPI_CSN_L()  GPIO_ResetBits(NRF24l01_CSN_GPIO, NRF24l01_CSN_PIN)

void Spi2_Init(void);

#endif
u8 Spi_RW(u8 dat);

#endif

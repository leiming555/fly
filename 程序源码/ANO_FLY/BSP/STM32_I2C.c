#include "STM32_I2C.h"


#define SCL_H         I2C_SCL_GPIO->BSRR =I2C_SCL_PIN  /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */
#define SCL_L         I2C_SCL_GPIO->BRR  =I2C_SCL_PIN  /* GPIO_ResetBits(GPIOB , GPIO_Pin_10) */
                                           
#define SDA_H         I2C_SDA_GPIO->BSRR =I2C_SDA_PIN  /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */
#define SDA_L         I2C_SDA_GPIO->BRR  =I2C_SDA_PIN  /* GPIO_ResetBits(GPIOB , GPIO_Pin_11) */
                                                                      
#define SCL_read      I2C_SCL_GPIO->IDR  &I2C_SCL_PIN  /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) */
#define SDA_read      I2C_SDA_GPIO->IDR  &I2C_SDA_PIN  /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */



static void I2C_delay(void)
{
    volatile int i = 7;
    while (i)
        i--;
}

static bool I2C_Start(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    if (!SDA_read)
        return false;
    SDA_L;
    I2C_delay();
    if (SDA_read)
        return false;
    SDA_L;
    I2C_delay();
    return true;
}

static void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}

static void I2C_Ack(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

static void I2C_NoAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

static bool I2C_WaitAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    if (SDA_read) {
        SCL_L;
        return false;
    }
    SCL_L;
    return true;
}

static void I2C_SendByte(uint8_t byte)
{
    uint8_t i = 8;
    while (i--) {
        SCL_L;
        I2C_delay();
        if (byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}

static uint8_t I2C_ReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t byte = 0;

    SDA_H;
    while (i--) {
        byte <<= 1;
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        if (SDA_read) {
            byte |= 0x01;
        }
    }
    SCL_L;
    return byte;
}

void i2cInit(void)
{
	  GPIO_InitTypeDef I2C_GPIO;
	
	  RCC_APB2PeriphClockCmd(RCC_I2C_SCL, ENABLE); //使能Px端口时钟
    I2C_GPIO.GPIO_Pin = I2C_SCL_PIN;
    I2C_GPIO.GPIO_Speed = GPIO_Speed_10MHz;
    I2C_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(I2C_SCL_GPIO, &I2C_GPIO);
	
	  RCC_APB2PeriphClockCmd(RCC_I2C_SDA, ENABLE); //使能Px端口时钟
    I2C_GPIO.GPIO_Pin = I2C_SDA_PIN;
	  I2C_GPIO.GPIO_Speed = GPIO_Speed_2MHz;//GPIO_Speed_10MHz;
    I2C_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(I2C_SDA_GPIO, &I2C_GPIO);
}

bool i2cWriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
{
    int i;
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr);// << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    for (i = 0; i < len; i++) {
        I2C_SendByte(data[i]);
        if (!I2C_WaitAck()) {
            I2C_Stop();
            return false;
        }
    }
    I2C_Stop();
    return true;
}

bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr);// << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
    return true;
}

bool i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr );//<< 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(addr+1);// << 1 | I2C_Direction_Receiver);
    I2C_WaitAck();
    while (len) {
        *buf = I2C_ReceiveByte();
        if (len == 1)
            I2C_NoAck();
        else
            I2C_Ack();
        buf++;
        len--;
    }
    I2C_Stop();
    return true;
}

uint16_t i2cGetErrorCounter(void)
{
    // TODO maybe fix this, but since this is test code, doesn't matter.
    return 0;
}

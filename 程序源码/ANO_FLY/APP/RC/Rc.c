#include "rc.h"
#include "bsp/bsp.h"
#include "app/uart/uart1.h"
#include "app/imu/imu.h"
#include "app/control/control.h"
#include "stdio.h"

//将数据 转换为二进制 传输
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define RX_DR           6       //中断标志
#define TX_DS           5
#define MAX_RT          4

RC_GETDATA Rc_Get;//接收到的RC数据,1000~2000
float RC_Target_ROL = 0, RC_Target_PIT = 0, RC_Target_YAW = 0;

void RC_FUN(void)
{
    //判断解锁
    static u16 _armed_cnt1 = 0, _armed_cnt2 = 0;
    if (ARMED == 0 && Rc_Get.THROTTLE < 1100 && Rc_Get.YAW < 1100)
        _armed_cnt1++;
    else
        _armed_cnt1 = 0;
    if (_armed_cnt1 > 100) ARMED = 1;       //解锁

    if (ARMED == 1 && Rc_Get.THROTTLE < 1100 && Rc_Get.YAW > 1900)
        _armed_cnt2++;
    else
        _armed_cnt2 = 0;
    if (_armed_cnt2 > 100) ARMED = 0;
}
/*
0x8A 遥控数据
0x8B,为控制数据
*/
void NRF_DataAnl(void)
{
    u8 sum = 0;
    for (u8 i = 0; i < 31; i++)
        sum += NRF24L01_RXDATA[i];
    if (!(sum == NRF24L01_RXDATA[31]))     return;  //判断sum//校验
    if (!(NRF24L01_RXDATA[0] == 0x8A))     return;  //判断帧头
    if (NRF24L01_RXDATA[1] == 0x8A)                 //判断功能字,=0x8a,为遥控数据
    {
        Rc_Get.THROTTLE     = (vs16)(NRF24L01_RXDATA[3] << 8) | NRF24L01_RXDATA[ 4];
        Rc_Get.YAW          = (vs16)(NRF24L01_RXDATA[5] << 8) | NRF24L01_RXDATA[ 6];
        Rc_Get.ROLL         = (vs16)(NRF24L01_RXDATA[7] << 8) | NRF24L01_RXDATA[ 8];
        Rc_Get.PITCH        = (vs16)(NRF24L01_RXDATA[9] << 8) | NRF24L01_RXDATA[10];
        Rc_Get.AUX1         = (vs16)(NRF24L01_RXDATA[11] << 8) | NRF24L01_RXDATA[12];
        Rc_Get.AUX2         = (vs16)(NRF24L01_RXDATA[13] << 8) | NRF24L01_RXDATA[14];
        Rc_Get.AUX3         = (vs16)(NRF24L01_RXDATA[15] << 8) | NRF24L01_RXDATA[16];
        Rc_Get.AUX4         = (vs16)(NRF24L01_RXDATA[17] << 8) | NRF24L01_RXDATA[18];
        Rc_Get.AUX5         = (vs16)(NRF24L01_RXDATA[19] << 8) | NRF24L01_RXDATA[20];
        RC_FUN(); //判断解锁
        RC_Target_ROL = (Rc_Get.ROLL - 1500) / 80;//遥控目标的 横滚
        RC_Target_PIT = (Rc_Get.PITCH - 1500) / 65;
        RC_Target_YAW = (Rc_Get.YAW - 1500) / 50;
    }
    if (NRF24L01_RXDATA[1] == 0X8B)                       //判断功能字,=0x8B,为控制数据
    {
        if (NRF24L01_RXDATA[3] == 0xAA) //校准传感器
        {
            if (NRF24L01_RXDATA[4] == 0xA2)    GYRO_OFFSET_OK = 0;
            if (NRF24L01_RXDATA[4] == 0xA1)    ACC_OFFSET_OK = 0;
            if (NRF24L01_RXDATA[4] == 0xA3)    {
                GYRO_OFFSET_OK = 0;
                ACC_OFFSET_OK = 0;
            }
        }
        if (NRF24L01_RXDATA[3] == 0xA0)
        {
            ARMED = 0;
            NRF_Send_ARMED();
        }
        if (NRF24L01_RXDATA[3] == 0xA1)
        {
            ARMED = 1;
            NRF_Send_ARMED();
        }
        if (NRF24L01_RXDATA[3] == 0xAB) //接收OFFSET
        {
            ACC_OFFSET.X = (NRF24L01_RXDATA[4] << 8) + NRF24L01_RXDATA[5];
            ACC_OFFSET.Y = (NRF24L01_RXDATA[6] << 8) + NRF24L01_RXDATA[7];
            EE_SAVE_ACC_OFFSET();//模拟EEROM 保存加速度数据
            //EE_SAVE_GYRO_OFFSET();
        }
        if (NRF24L01_RXDATA[3] == 0xAC)    NRF_Send_OFFSET();
        if (NRF24L01_RXDATA[3] == 0xAD)    NRF_Send_PID();
        if (NRF24L01_RXDATA[3] == 0xAE) //接收PID
        {
            PID_ROL.P = (float)((vs16)(NRF24L01_RXDATA[4] << 8) | NRF24L01_RXDATA[5]) / 100;
            PID_ROL.I = (float)((vs16)(NRF24L01_RXDATA[6] << 8) | NRF24L01_RXDATA[7]) / 100;
            PID_ROL.D = (float)((vs16)(NRF24L01_RXDATA[8] << 8) | NRF24L01_RXDATA[9]) / 100;
            PID_PIT.P = (float)((vs16)(NRF24L01_RXDATA[10] << 8) | NRF24L01_RXDATA[11]) / 100;
            PID_PIT.I = (float)((vs16)(NRF24L01_RXDATA[12] << 8) | NRF24L01_RXDATA[13]) / 100;
            PID_PIT.D = (float)((vs16)(NRF24L01_RXDATA[14] << 8) | NRF24L01_RXDATA[15]) / 100;
            PID_YAW.P = (float)((vs16)(NRF24L01_RXDATA[16] << 8) | NRF24L01_RXDATA[17]) / 100;
            PID_YAW.I = (float)((vs16)(NRF24L01_RXDATA[18] << 8) | NRF24L01_RXDATA[19]) / 100;
            PID_YAW.D = (float)((vs16)(NRF24L01_RXDATA[20] << 8) | NRF24L01_RXDATA[21]) / 100;
            EE_SAVE_PID();//EEROM 保存PID数据
        }
    }
}
void Nrf_Check_Event(void)
{
    u8 sta = NRF_Read_Reg(NRF_READ_REG + NRFRegSTATUS);
    ////////////////////////////////////////////////////////////////
    if (sta & (1 << RX_DR))//判断 是否是接受中断
    {
        u8 rx_len = NRF_Read_Reg(R_RX_PL_WID);
        if (rx_len < 33)//判断接受数据长度
        {
            NRF_Read_Buf(RD_RX_PLOAD, NRF24L01_RXDATA, RX_PLOAD_WIDTH); // read receive payload from RX_FIFO buffer
            NRF_DataAnl();
            LED1_ONOFF();
        }
        else//数据有误
        {
            NRF_Write_Reg(FLUSH_RX, 0xff); //清空缓冲区
        }
    }
    ////////////////////////////////////////////////////////////////
    if (sta & (1 << TX_DS))//判断 是否是发送中断
    {
        LED1_ONOFF();
    }
    ////////////////////////////////////////////////////////////////
    static uint8_t led2_state = 0;
    if (sta & (1 << MAX_RT))//异常中断	
    {
        if (led2_state)
        {
            LED2_OFF;
            led2_state = 0;
        }
        else
        {
            LED2_ON;
            led2_state = 1;
        }
        if (sta & 0x01) //TX FIFO FULL
        {
            NRF_Write_Reg(FLUSH_TX, 0xff);
        }
    }
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    NRF_Write_Reg(NRF_WRITE_REG + NRFRegSTATUS, sta);//NRF写一清除中断
}
void NRF_Send_AF(void)
{
    uint8_t i, sum;
    uint16_t _temp;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xAF;
    NRF24L01_TXDATA[2] = 0x1C;
//1
    NRF24L01_TXDATA[3] = BYTE1(MPU6050_ACC_LAST.X);
    NRF24L01_TXDATA[4] = BYTE0(MPU6050_ACC_LAST.X);
//2	
    NRF24L01_TXDATA[5] = BYTE1(MPU6050_ACC_LAST.Y);
    NRF24L01_TXDATA[6] = BYTE0(MPU6050_ACC_LAST.Y);
//3   
	NRF24L01_TXDATA[7] = BYTE1(MPU6050_ACC_LAST.Z);
    NRF24L01_TXDATA[8] = BYTE0(MPU6050_ACC_LAST.Z);
//4   
	NRF24L01_TXDATA[9] = BYTE1(MPU6050_GYRO_LAST.X);
    NRF24L01_TXDATA[10] = BYTE0(MPU6050_GYRO_LAST.X);
//5   
	NRF24L01_TXDATA[11] = BYTE1(MPU6050_GYRO_LAST.Y);
    NRF24L01_TXDATA[12] = BYTE0(MPU6050_GYRO_LAST.Y);
//6   
	 NRF24L01_TXDATA[13] = BYTE1(MPU6050_GYRO_LAST.Z);
    NRF24L01_TXDATA[14] = BYTE0(MPU6050_GYRO_LAST.Z);
  
  NRF24L01_TXDATA[15] = 0;
    NRF24L01_TXDATA[16] = 0;
    NRF24L01_TXDATA[17] = 0;
    NRF24L01_TXDATA[18] = 0;
    NRF24L01_TXDATA[19] = 0;
    NRF24L01_TXDATA[20] = 0;
    _temp = (int)(Q_ANGLE.X * 100);
    NRF24L01_TXDATA[21] = BYTE1(_temp);
    NRF24L01_TXDATA[22] = BYTE0(_temp);
    _temp = (int)(Q_ANGLE.Y * 100);
    NRF24L01_TXDATA[23] = BYTE1(_temp);
    NRF24L01_TXDATA[24] = BYTE0(_temp);
    _temp = (int)(Q_ANGLE.Z * 10);
    NRF24L01_TXDATA[25] = BYTE1(_temp);
    NRF24L01_TXDATA[26] = BYTE0(_temp);

    if (ARMED == 0)            NRF24L01_TXDATA[27] = 0xA0;
    else if (ARMED == 1)       NRF24L01_TXDATA[27] = 0xA1;

    sum = 0;
    for (i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}
void NRF_Send_AE(void)
{
    uint8_t i, sum;
    uint16_t _temp;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xAE;
    NRF24L01_TXDATA[2] = 0x1C;
    NRF24L01_TXDATA[3] = BYTE1(Rc_Get.THROTTLE);
    NRF24L01_TXDATA[4] = BYTE0(Rc_Get.THROTTLE);
    NRF24L01_TXDATA[5] = BYTE1(Rc_Get.YAW);
    NRF24L01_TXDATA[6] = BYTE0(Rc_Get.YAW);
    NRF24L01_TXDATA[7] = BYTE1(Rc_Get.ROLL);
    NRF24L01_TXDATA[8] = BYTE0(Rc_Get.ROLL);
    NRF24L01_TXDATA[9] = BYTE1(Rc_Get.PITCH);
    NRF24L01_TXDATA[10] = BYTE0(Rc_Get.PITCH);
    NRF24L01_TXDATA[11] = BYTE1(Rc_Get.AUX1);
    NRF24L01_TXDATA[12] = BYTE0(Rc_Get.AUX1);
    NRF24L01_TXDATA[13] = BYTE1(Rc_Get.AUX2);
    NRF24L01_TXDATA[14] = BYTE0(Rc_Get.AUX2);
    NRF24L01_TXDATA[15] = BYTE1(Rc_Get.AUX3);
    NRF24L01_TXDATA[16] = BYTE0(Rc_Get.AUX3);
    NRF24L01_TXDATA[17] = BYTE1(Rc_Get.AUX4);
    NRF24L01_TXDATA[18] = BYTE0(Rc_Get.AUX4);
    NRF24L01_TXDATA[19] = BYTE1(Rc_Get.AUX5);
    NRF24L01_TXDATA[20] = BYTE0(Rc_Get.AUX5);

    _temp = TIM2->CCR1 / 20;
    NRF24L01_TXDATA[21] = BYTE1(_temp);
    NRF24L01_TXDATA[22] = BYTE0(_temp);
    _temp = TIM2->CCR2 / 20;
    NRF24L01_TXDATA[23] = BYTE1(_temp);
    NRF24L01_TXDATA[24] = BYTE0(_temp);
		_temp = (TIM8->CCR1) /20;
    NRF24L01_TXDATA[25] = BYTE1(_temp);
    NRF24L01_TXDATA[26] = BYTE0(_temp);
		_temp = (TIM8->CCR2) /20;
    NRF24L01_TXDATA[27] = BYTE1(_temp);
    NRF24L01_TXDATA[28] = BYTE0(_temp);
    _temp = ADC_ConvertedValue / 6;
    NRF24L01_TXDATA[29] = BYTE1(_temp);
    NRF24L01_TXDATA[30] = BYTE0(_temp);

    sum = 0;
    for (i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}
void NRF_Send_OFFSET(void)
{
    uint8_t i, sum;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xAC;
    NRF24L01_TXDATA[2] = 0x1C;
    NRF24L01_TXDATA[3] = 0xAC;
    NRF24L01_TXDATA[4] = BYTE1(ACC_OFFSET.X);
    NRF24L01_TXDATA[5] = BYTE0(ACC_OFFSET.X);
    NRF24L01_TXDATA[6] = BYTE1(ACC_OFFSET.Y);
    NRF24L01_TXDATA[7] = BYTE0(ACC_OFFSET.Y);
    NRF24L01_TXDATA[8] = BYTE1(ACC_OFFSET.Z);
    NRF24L01_TXDATA[9] = BYTE0(ACC_OFFSET.Z);
    NRF24L01_TXDATA[10] = BYTE1(GYRO_OFFSET.X);
    NRF24L01_TXDATA[11] = BYTE0(GYRO_OFFSET.X);
    NRF24L01_TXDATA[12] = BYTE1(GYRO_OFFSET.Y);
    NRF24L01_TXDATA[13] = BYTE0(GYRO_OFFSET.Y);
    NRF24L01_TXDATA[14] = BYTE1(GYRO_OFFSET.Z);
    NRF24L01_TXDATA[15] = BYTE0(GYRO_OFFSET.Z);
    sum = 0;
    for (i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}
void NRF_Send_PID(void)
{
    uint8_t i, sum;
    u16 _temp;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xAC;
    NRF24L01_TXDATA[2] = 0x1C;
    NRF24L01_TXDATA[3] = 0xAD;

    _temp = PID_ROL.P * 100;
    NRF24L01_TXDATA[4] = BYTE1(_temp);
    NRF24L01_TXDATA[5] = BYTE0(_temp);
    _temp = PID_ROL.I * 100;
    NRF24L01_TXDATA[6] = BYTE1(_temp);
    NRF24L01_TXDATA[7] = BYTE0(_temp);
    _temp = PID_ROL.D * 100;
    NRF24L01_TXDATA[8] = BYTE1(_temp);
    NRF24L01_TXDATA[9] = BYTE0(_temp);
    _temp = PID_PIT.P * 100;
    NRF24L01_TXDATA[10] = BYTE1(_temp);
    NRF24L01_TXDATA[11] = BYTE0(_temp);
    _temp = PID_PIT.I * 100;
    NRF24L01_TXDATA[12] = BYTE1(_temp);
    NRF24L01_TXDATA[13] = BYTE0(_temp);
    _temp = PID_PIT.D * 100;
    NRF24L01_TXDATA[14] = BYTE1(_temp);
    NRF24L01_TXDATA[15] = BYTE0(_temp);
    _temp = PID_YAW.P * 100;
    NRF24L01_TXDATA[16] = BYTE1(_temp);
    NRF24L01_TXDATA[17] = BYTE0(_temp);
    _temp = PID_YAW.I * 100;
    NRF24L01_TXDATA[18] = BYTE1(_temp);
    NRF24L01_TXDATA[19] = BYTE0(_temp);
    _temp = PID_YAW.D * 100;
    NRF24L01_TXDATA[20] = BYTE1(_temp);
    NRF24L01_TXDATA[21] = BYTE0(_temp);

    sum = 0;
    for (i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}
void NRF_Send_ARMED(void)//解锁信息
{
    uint8_t i, sum;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xAC;
    NRF24L01_TXDATA[2] = 0x1C;
    if (ARMED)   NRF24L01_TXDATA[3] = 0xA1;
    else         NRF24L01_TXDATA[3] = 0xA0;
    sum = 0;
    for (i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}
void NRF_SEND_test(void)
{
    u8 sum;

    static u8 temp = 0;

    temp++;

    NRF24L01_TXDATA[0] = 0x88;
    NRF24L01_TXDATA[1] = 0xA1;
    NRF24L01_TXDATA[2] = 28;
    NRF24L01_TXDATA[3] = BYTE3(Q_ANGLE.X);
    NRF24L01_TXDATA[4] = BYTE2(Q_ANGLE.X);
    NRF24L01_TXDATA[5] = BYTE1(Q_ANGLE.X);
    NRF24L01_TXDATA[6] = BYTE0(Q_ANGLE.X);
    NRF24L01_TXDATA[7] = BYTE3(Q_ANGLE.Y);
    NRF24L01_TXDATA[8] = BYTE2(Q_ANGLE.Y);
    NRF24L01_TXDATA[9] = BYTE1(Q_ANGLE.Y);
    NRF24L01_TXDATA[10] = BYTE0(Q_ANGLE.Y);

    NRF24L01_TXDATA[11] = temp;

    for (u8 i = 0; i < 31; i++)
        sum += NRF24L01_TXDATA[i];

    NRF24L01_TXDATA[31] = sum;

    NRF_TxPacket(NRF24L01_TXDATA, 32);
}


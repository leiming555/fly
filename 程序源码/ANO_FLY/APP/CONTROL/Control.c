#include "control.h"
#include "BSP/BSP.H"
#include "app/rc/rc.h"
#include "app/imu/imu.h"

PID PID_ROL, PID_PIT, PID_YAW;
u8 ARMED = 0;

float Get_MxMi(float num, float max, float min)
{
    if (num > max)
        return max;
    else if (num < min)
        return min;
    else
        return num;
}

void CONTROL(float rol_now, float pit_now, float yaw_now, float rol_tar, float pit_tar, float yaw_tar)
{
    u16 moto1 = 0, moto2 = 0, moto3 = 0, moto4 = 0;
    vs16 throttle;

    float rol = rol_tar + rol_now;
    float pit = pit_tar + pit_now;
    float yaw = yaw_tar + yaw_now;

    throttle = Rc_Get.THROTTLE - 1000;//ÓÍÃÅ ½ÚÁ÷·§
    if (throttle < 0)  throttle = 0;

    PID_ROL.IMAX = throttle / 2;
    Get_MxMi(PID_ROL.IMAX, 1000, 0);
    PID_PIT.IMAX = PID_ROL.IMAX;

    PID_ROL.pout = PID_ROL.P * rol;
    PID_PIT.pout = PID_PIT.P * pit;

    if (rol_tar * rol_tar < 0.1 && pit_tar * pit_tar < 0.1 && rol_now * rol_now < 30 && pit_now * pit_now < 30 && throttle > 300)
    {
        PID_ROL.iout += PID_ROL.I * rol;
        PID_PIT.iout += PID_PIT.I * pit;
        PID_ROL.iout = Get_MxMi(PID_ROL.iout, PID_ROL.IMAX, -PID_ROL.IMAX);
        PID_PIT.iout = Get_MxMi(PID_PIT.iout, PID_PIT.IMAX, -PID_PIT.IMAX);
    }
    else if (throttle < 200)
    {
        PID_ROL.iout = 0;
        PID_PIT.iout = 0;
    }

    PID_ROL.dout = PID_ROL.D * MPU6050_GYRO_LAST.X;
    PID_PIT.dout = PID_PIT.D * MPU6050_GYRO_LAST.Y;

    PID_YAW.pout = PID_YAW.P * yaw;
    vs16 yaw_d;
    if (1480 > Rc_Get.YAW || Rc_Get.YAW > 1520)
    {
        yaw_d = MPU6050_GYRO_LAST.Z + (Rc_Get.YAW - 1500) * 10;
        GYRO_I.Z = 0;
    }
    else
        yaw_d = MPU6050_GYRO_LAST.Z;
    PID_YAW.dout = PID_YAW.D * yaw_d;

    PID_ROL.OUT = PID_ROL.pout + PID_ROL.iout + PID_ROL.dout;
    PID_PIT.OUT = PID_PIT.pout + PID_PIT.iout + PID_PIT.dout;
    PID_YAW.OUT = PID_YAW.pout + PID_YAW.iout + PID_YAW.dout;

		/*
		rol ·­¹ö
		pat ¸©Ñö½Ç
		yaw //Æ«º½
		*/
    if (throttle > 200)
    {
			#define YAW_ADD (-30)
        moto1 = throttle + PID_ROL.OUT - PID_PIT.OUT +YAW_ADD+ PID_YAW.OUT/**/;
        moto2 = throttle - PID_ROL.OUT - PID_PIT.OUT -YAW_ADD- PID_YAW.OUT/**/;
        moto3 = throttle - PID_ROL.OUT + PID_PIT.OUT +YAW_ADD+ PID_YAW.OUT/**/;
        moto4 = throttle + PID_ROL.OUT + PID_PIT.OUT -YAW_ADD- PID_YAW.OUT/**/;
    }
    else
    {
        moto1 = 0;
        moto2 = 0;
        moto3 = 0;
        moto4 = 0;
    }
    if (ARMED)   Moto_PwmRflash(moto1, moto2, moto3, moto4);
    else         Moto_PwmRflash(0, 0, 0, 0);
}


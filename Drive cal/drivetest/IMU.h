//IMU_I2C header file
//2015.06.26
//2015.07.03 modify by Kwon Hwi Jae
#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include <Wire.h>

#define WHO_AM_I 0x01
#define REV_ID_MAJOR 0x02
#define REV_ID_MINOR 0x03
#define STATUS 0x04
#define I_ACC_X_LOW 0x10
#define I_ACC_X_HIGH 0x11
#define I_ACC_Y_LOW 0x12
#define I_ACC_Y_HIGH 0x13
#define I_ACC_Z_LOW 0x14
#define I_ACC_Z_HIGH 0x15
#define I_GYRO_X_LOW 0x16
#define I_GYRO_X_HIGH 0x17
#define I_GYRO_Y_LOW 0x18
#define I_GYRO_Y_HIGH 0x19
#define ADDRESS 0x20
#define I_GYRO_Z_LOW 0x1A
#define I_GYRO_Z_HIGH 0x1B
#define I_MAGNET_X_LOW 0x1C
#define I_MAGNET_X_HIGH 0x1D
#define I_MAGNET_Y_LOW 0x1E
#define I_MAGNET_Y_HIGH 0x1F
#define I_MAGNET_Z_LOW 0x20
#define I_MAGNET_Z_HIGH 0x21
#define C_ACC_X_LOW 0x22
#define C_ACC_X_HIGH 0x23
#define C_ACC_Y_LOW 0x24
#define C_ACC_Y_HIGH 0x25
#define C_ACC_Z_LOW 0x26
#define C_ACC_Z_HIGH 0x27
#define C_GYRO_X_LOW 0x28
#define C_GYRO_X_HIGH 0x29
#define C_GYRO_Y_LOW 0x2A
#define C_GYRO_Y_HIGH 0x2B
#define C_GYRO_Z_LOW 0x2C
#define C_GYRO_Z_HIGH 0x2D
#define C_MAGNET_X_LOW 0x2E
#define C_MAGNET_X_HIGH 0x2F
#define C_MAGNET_Y_LOW 0x30
#define C_MAGNET_Y_HIGH 0x31
#define C_MAGNET_Z_LOW 0x32
#define C_MAGNET_Z_HIGH 0x33
#define TEMPERATURE_LOW 0x34
#define TEMPERATURE_HIGH 0x35
#define ROLL_LOW 0x36
#define ROLL_HIGH 0x37
#define PITCH_LOW 0x38
#define PITCH_HIGH 0x39
#define YAW_LOW 0x3A
#define YAW_HIGH 0x3B
#define QUATERNION_X_LOW 0x3C
#define QUATERNION_X_HIGH 0x3D
#define QUATERNION_Y_LOW 0x3E
#define QUATERNION_Y_HIGH 0x3F
#define QUATERNION_Z_LOW 0x40
#define QUATERNION_Z_HIGH 0x41
#define QUATERNION_W_LOW 0x42
#define QUATERNION_W_HIGH 0x43


class IMU{
public:

   IMU();
   int renew();
   void initiate();
   double getWHO_AM_I();
   double getSTATUS();

   //double Status();
   double getRoll();
   double getPitch();
   double getYaw();
   double getGyroX();
   double getGyroY();
   double getGyroZ();
   double getAccX();
   double getAccY();
   double getAccZ();
   double getTem();
   String getSYaw();
   String getSGyroZ();
   

   uint8_t readRegister8(uint8_t Reg, double ft);

private:
  
   double status;
   double who_am_i;
   double Status;

   double roll;
   double rollL;
   double rollH;

   double pitch;
   double pitchL;
   double pitchH;

   double yaw;
   double yawL;
   double yawH;
   
   double gyroX;
   double gyroXL;
   double gyroXH;

   double gyroY;
   double gyroYL;
   double gyroYH;

   double gyroZ;
   double gyroZL;
   double gyroZH;
   
   double accX;
   double accXL;
   double accXH;

   double accY;
   double accYL;
   double accYH;

   double accZ;
   double accZL;
   double accZH;

   double temperature;
   double temperatureL;
   double temperatureH;
};

#endif

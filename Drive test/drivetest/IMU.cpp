//IMU_I2C cpp file
//2015.6.26
//I2C Communication
//Kim Ju Hyeon
//2015.07.03 modify by Kwon Hwi Jae

#include <Wire.h>
#include "IMU.h"
#include "Arduino.h"

IMU::IMU(){
   status = 0;
   who_am_i = 0;
   Status = 0;

   roll = 0;
   rollL = 0;
   rollH = 0;
   pitch = 0;
   pitchL = 0;
   pitchH = 0;
   yaw = 0;
   yawL = 0;
   yawH = 0;
   gyroX = 0;
   gyroXL = 0;
   gyroXH = 0;
   gyroY = 0;
   gyroYL = 0;
   gyroYH = 0;
   gyroZ = 0;
   gyroZL = 0;
   gyroZH = 0;

   accX = 0;
   accXL = 0;
   accXH = 0;
   accY = 0;
   accYL = 0;
   accYH = 0;
   accZ = 0;
   accZL = 0;
   accZH = 0;
   temperature = 0;
   temperatureL = 0;
   temperatureH = 0;
}

double IMU::getWHO_AM_I() { return who_am_i;}
double IMU::getSTATUS() { return Status;}

uint8_t IMU::readRegister8(uint8_t Reg, double ft){
   uint8_t value;
  Wire.beginTransmission(ADDRESS);
   
   #if ARDUINO >= 100
      Wire.write(Reg);
   #else
      Wire.send(Reg);
   #endif

   Wire.endTransmission(false);

   Wire.beginTransmission(ADDRESS);
   Wire.requestFrom(ADDRESS, 1);
   if(Wire.available() == false){ //stuck
      return ft;
   }

   #if ARDUINO >= 100
      value = Wire.read();

   #else
      value = Wire.receive();
   #endif

   Wire.endTransmission();

   return value;
}

int IMU::renew(){  
   status = readRegister8(STATUS, status);

   rollL = readRegister8(ROLL_LOW, rollL);
   rollH = readRegister8(ROLL_HIGH, rollH);

   roll = (rollL+(256*rollH))*180/32767;

   pitchL = readRegister8(PITCH_LOW, pitchL);
   pitchH = readRegister8(PITCH_HIGH, pitchH);

   pitch = (pitchL+(256*pitchH))*180/32767;

   yawL = readRegister8(YAW_LOW, yawL);
   yawH = readRegister8(YAW_HIGH, yawH);

   yaw = (yawL+(256*yawH))*180/32767;

   gyroXL= readRegister8(C_GYRO_X_LOW, gyroXL);
   gyroXH= readRegister8(C_GYRO_X_HIGH, gyroXH);

   gyroX = (gyroXL+(256*gyroXH))*2000/32767;
   if(gyroX > 2000){
      gyroX = gyroX - 4000;
   }

   gyroYL= readRegister8(C_GYRO_Y_LOW, gyroYL);
   gyroYH= readRegister8(C_GYRO_Y_HIGH, gyroYH);

   gyroY = (gyroYL+(256*gyroYH))*2000/32767;
   if(gyroY > 2000){
      gyroY = gyroY - 4000;
   }

   gyroZL= readRegister8(C_GYRO_Z_LOW, gyroZL);
   gyroZH= readRegister8(C_GYRO_Z_HIGH, gyroZH);

   gyroZ = (gyroZL+(256*gyroZH))*2000/32767;
   if(gyroZ > 2000){
      gyroZ = gyroZ - 4000;
   }

   accXL= readRegister8(C_ACC_X_LOW, accXL);
   accXH= readRegister8(C_ACC_X_HIGH, accXH);

   accX = (accXL+(256*accXH))*16/32767;

   accYL= readRegister8(C_ACC_Y_LOW, accYL);
   accYH= readRegister8(C_ACC_Y_HIGH, accYH);

   accY = (accYL+(256*accYH))*16/32767;

   accZL= readRegister8(C_ACC_Z_LOW, accZL);
   accZH= readRegister8(C_ACC_Z_HIGH, accZH);

   accZ = (accZL+(256*accZH))*16/32767;

   temperatureL = readRegister8(TEMPERATURE_LOW, temperatureL);
   temperatureH = readRegister8(TEMPERATURE_HIGH, temperatureH);

   temperature = (temperatureL+(256*temperatureH))*200/32767;
}

void IMU::initiate(){
  Wire.begin();
  who_am_i = readRegister8(WHO_AM_I, -1);
  Status = readRegister8(STATUS, -1);
}

String IMU::getSYaw()
{
  long int a = yaw*1000;
  return String(a);
}

String IMU::getSGyroZ()
{
  long int a = gyroZ*1000;
  return String(a);
}

//double IMU::Status(){return status;}
double IMU::getRoll(){return roll;}
double IMU::getPitch(){return pitch;}
double IMU::getYaw(){return yaw;}
double IMU::getGyroX(){return gyroX;}
double IMU::getGyroY(){return gyroY;}
double IMU::getGyroZ(){return gyroZ;}
double IMU::getAccX(){return accX;}
double IMU::getAccY(){return accY;}
double IMU::getAccZ(){return accZ;}
double IMU::getTem(){return temperature;}

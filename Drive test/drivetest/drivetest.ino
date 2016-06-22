  
#include "IMU.h"
#include "Drive.h"
#include "MAX.h"
#include "ESP8266_P2P.h"

#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define goalLat 3727.35477//3727.63174//3727.35477
#define goalLng 12657.06689//12657.03642//12657.06689

IMU imu;
MAX gps;
ESP8266_P2P wifi;
Drive drive;

void setup() 
{
  Serial.begin(9600);
  imu.initiate();
  gps.MAXstart();
  //wifi.startESP();
  delay(500);
  //Serial.println(wifi.getReadyIP());
  //delay(1000);
  
  imu.renew();
  gps.renew();
  double yaw = imu.getYaw();
  double gyroZ = imu.getGyroZ();
  double lat = gps.getLat();
  double lng = gps.getLng();
  String slat = gps.getSLat();
  String slng = gps.getSLng(); 
  
  while((lat==0)&&(lng==0))
  {
  imu.renew();
  gps.renew();
  double yaw = imu.getYaw();
  double gyroZ = imu.getGyroZ();
  double lat = gps.getLat();
  double lng = gps.getLng();
  String slat = gps.getSLat();
  String slng = gps.getSLng(); 
  Datasend(yaw, gyroZ, lat, lng);
  
  //wifi.Print(slat);
 // wifi.Println(slng);
  //wifi.Print(yaw);
  //wifi.Println(gyroZ);
  }
  drive.initiate(goalLat, goalLng);
  drive.stop();
  delay(4000);
}


void loop() 
{ 
  imu.renew();
  gps.renew();
  
  double yaw = imu.getYaw();
  double gyroZ = imu.getGyroZ();
  double lat = gps.getLat();
  double lng = gps.getLng();
  String slat = gps.getSLat();
  String slng = gps.getSLng(); 
  
  drive.update(lat, lng, yaw, gyroZ);
  drive.gotoGoal();
 
  Datasend(yaw, gyroZ, lat, lng);
  
 // wifi.Print(slat);
 // wifi.Println(slng);
  //wifi.Print(yaw);
//wifi.Println(gyroZ);
  
 /* if(wifi.stop())
  {
    drive.stop();
    while(1);
  }*/
}

void Datasend(double yaw, double gyroZ, double lat, double lng)
{
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(gyroZ);
  Serial.print(" ");
  Serial.print(lat);
  Serial.print(" ");
  Serial.println(lng);
  delay(1000);
}
  


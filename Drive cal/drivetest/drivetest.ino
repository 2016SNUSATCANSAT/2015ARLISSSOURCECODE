  
#include "IMU.h"
#include "Drive2.h"
#include "MAX.h"
#include "ESP8266_P2P2.h"

#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define goalLat 1//3727.35477
#define goalLng 0//12657.06689

IMU imu;
MAX gps;
ESP8266_P2P wifi;
Drive drive;

void setup() 
{
  Serial.begin(9600);
  
  imu.initiate();
 // gps.MAXstart();
  wifi.startESP();
  Serial.println(wifi.getReadyIP());
  drive.initiate(goalLat, goalLng);
  drive.stop();
}


void loop() 
{ 
  imu.renew();
 // gps.renew();
  
  double yaw = imu.getYaw();
  double gyroZ = imu.getGyroZ();
//  double lat = gps.getLat();
//  double lng = gps.getLng();
//  String slat = gps.getSLat();
//  String slng = gps.getSLng(); 
  drive.update(0,0, yaw, gyroZ);
  
  int set = 0;
  set = wifi.setvalue();
  Serial.println(set); //test
  
  if(set == 0) { drive.stop(); Serial.println("stop");}
  else if(set == 1) { drive.setvalue(0.0075, 1.0, 0.5, 100, 10); drive.gotoGoal(); Serial.println("case 1");}
  else if(set == 2) { drive.setvalue(0.0075, 1.0, 0.5, 300, 10); drive.gotoGoal(); Serial.println("case 2");}
  else if(set == 3) { drive.setvalue(0.0075, 1.0, 0.5, 500, 20); drive.gotoGoal(); Serial.println("case 3");}  

  
//  Datasend(yaw, gyroZ, 0, 0);

  
    
//  wifi.Print(slat);
//  wifi.Println(slng);
//  wifi.Print(yaw);
//  wifi.Println(gyroZ);
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
  


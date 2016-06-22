
#include "ESP8266_P2P.h" 
#include "IMU.h"
#include "MAX.h"
#include "Drive.h"

#include<SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

#define goalLat 23123
#define goalLng 123

ESP8266_P2P wifi;
IMU imu;
MAX gps;
//Drive drive;

void setup() 
{
  Serial.begin(9600);
 
  imu.initiate();
  gps.MAXstart();
  wifi.startESP();
  //drive.initiate(goalLat, goalLng);
  delay(500);
  /*Serial.println("wifi ready?");
  Serial.println(wifi.getReadyIP());
  Serial.println("imu ready?");
  Serial.print(imu.getWHO_AM_I());
  Serial.print(" ");
  Serial.println(imu.getSTATUS());
  delay(500);*/
}

int a = 0;

void loop() 
{ 
  gps.renew();
  imu.renew();
  
 
  double lat = gps.getLat();
  double lng = gps.getLng();
  double hgt = gps.getHgt();
  String slat = gps.getSLat();
  String slng = gps.getSLng();
  String shgt = gps.getSHgt();


  double yaw = imu.getYaw();
  double gyroZ = imu.getGyroZ();

  /*if((dlat!=0)||(dlng!=0))
  {
    drive.update(dlat, dlng, dyaw, dgyroZ);
    drive.gotoGoal();
  }*/
  
 //String data = lat + " " + lng + " " + hgt +" " +yaw + " " + gyroZ;


 //wifi.Println(data);
  wifi.Print(slat);
  wifi.Print(" ");
  wifi.Print(slng);
  wifi.Print(" ");
  wifi.Print(shgt);
  wifi.Print(" ");
  wifi.Print(yaw);
  wifi.Print(" ");
  wifi.Println(gyroZ);
  
 if(wifi.stop())
  {
    Serial.println("Stop signal");
    while(1);
  }
  a++;
  Datasend(a, yaw, gyroZ, lat, lng);
}

void Datasend(int a, double yaw, double gyroZ, double lat, double lng)
{
  Serial.print(a);
  Serial.print("  ");
  Serial.print(yaw);
  Serial.print("  ");
  Serial.print(gyroZ);
  Serial.print("  ");
  Serial.print(lat); 
  Serial.print("  ");
  Serial.println(lng);
  delay(1000);
}


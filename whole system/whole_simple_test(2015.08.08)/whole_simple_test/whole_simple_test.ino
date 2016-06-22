//whole system ino code
//2015.07.05 Kwon Hwi Jae
//WIFI.h not yet
//Mission.h not yet
//Camera.h not yet
//Some parameters need test
//skip datasend, store

//2015.08.07 simple test

#include "Flight.h"
#include "Waiting.h"
#include "Drive.h"
#include "Stuck.h"
#include "Safe.h"
//#include "Mission.h"

#include "MAX.h"
#include "ESP8266_P2P.h"
#include "IMU.h"
//#include "Camera.h"

#include "Time.h"

#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define goalLat 3727.35477
#define goalLng  12657.06689
#define heatpin 4 //digital 4 heatpin

MAX gps;
IMU imu;
ESP8266_P2P wifi;
//Camera camera;

Flight flight;
Waiting waiting;
Drive drive;
Stuck stuck;
Safe safe(goalLat, goalLng);
//Mission mission;

void setup()
{
	Serial.begin(9600);
	gps.MAXstart();
	wifi.startESP();
	delay(1000);

	gps.renew();//consider cold start 
	imu.initiate();
	delay(1000);

	int errorstate = 0;
	String Serrorstate = "";
	int wifierrornum1 = wifi.geterrornum1();
	int wifierrornum2 = wifi.geterrornum2();
	double who_am_i = imu.getWHO_AM_I();
	double status = imu.getSTATUS();
	int startmin = minute();

	flight.WIFIcheck(wifierrornum1, wifierrornum2);
	flight.IMUcheck(who_am_i, status);

	Stringprintln(wifi.getReadyIP()); //IP store

	delay(500);

	Stringprintln("lat lng yaw gyroZ");//data form

	while(flight.getflight()>0)//SAT is flying
	{
		gps.renew(); //consider cold start
		imu.renew();
		int mini = minute();
		int sec = second();
		double lat = gps.getLat();
		double lng = gps.getLng();
		double hgt = gps.getHgt();
		double deltaH = gps.getDeltaH();
		//IMU imformation 
   		double Yaw = imu.getYaw();
   		double GyroZ = imu.getGyroZ();
   		Dataprintln(mini, sec, lat, lng, hgt, Yaw, GyroZ);
		/*...
		data send
		...*/
		//flight.GPScheck1(lat, lng);
		//flight.FlightCheck(deltaH);
                flight.GPScheck1(lat, lng);
                flight.FlightCheck(3); //test

		if((minute()-startmin)>=1) { break;} //flight time limit 15min
	}
        Stringprintln("fight end");
	flight.GPScheck2(); //GPS 0,0 check
	errorstate = flight.getGPSError() + flight.getIMUError() + flight.getWIFIError(); //0 : Error, not 0 : not Error
	Serrorstate = flight.getSGPSError() + flight.getSIMUError() + flight.getSWIFIError();
        Stringprintln(flight.getSGPSError() + flight.getSIMUError() + flight.getSWIFIError());
	if(errorstate==0) {safe.setsafe(1); safe.setSsafe("Safe mode");} //error --> safemode
	else {waiting.setwaiting(1);} //no error --> waitingmode

	if(waiting.getwaiting()) //waiting mode
	{
                Serial.println("waiting mode"); //test	
		waiting.heatline(heatpin);//heat line for 10sec
		waiting.setwaiting(0); //waiting mode end
		drive.initiate(goalLat, goalLng); //motor on
                drive.stop();
		drive.setDrive(1); //drive mode start
	}
}
double lat = 0;
double lng = 0;
void loop()
{
	gps.renew();
	imu.renew();
	int min = minute();
	int sec = second();
	//double lat = gps.getLat();
	//double lng = gps.getLng();
         lat += 10;
         lng += 10;
	double hgt = gps.getHgt();
	double deltaH = gps.getDeltaH();
	//IMU imformation 
   	double Yaw = imu.getYaw();
   	double GyroZ = imu.getGyroZ();
   	Dataprintln(min, sec, lat, lng, hgt, Yaw, GyroZ);
   	
	//data send --> after drive
	
	
	if(safe.safecheck(lat, lng, wifi.stop(), stuck.getescapecount()))//safe check
	{
		drive.setDrive(0);
		stuck.setstuck(0);
		drive.stop();
		Stringprintln(safe.getSsafe());
		//wifi.Println(safe.getSsafe());
		delay(10000); //1min -> test 10sec
	}
	else if(drive.getDrive()>0)//drive mode
	{
		//drive.update(lat, lng, Yaw, GyroZ);
		//drive.gotoGoal();
                Serial.println("drive"); //test
		if(stuck.StuckCheck(lat,lng)) //stuck check 
		{
			Stringprintln(stuck.getSstuck());
			//wifi.Println(stuck.getSstuck());
			stuck.setstuck(1); 
			drive.stop();
			drive.setDrive(0);
		} 
		//mission condition check --> stop		
	}
	else if(stuck.getstuck()>0)//stuck mode
	{
		drive.stop();
		//drive.escape();
                Serial.println("drive escape"); //test 
		if(stuck.escape(lat, lng))//escape check
		{
                        
			Stringprintln(stuck.getSstuck());
			//wifi.Println(stuck.getSstuck());
                        stuck.setescapecount(0);			
			stuck.setstuck(0);
			drive.setDrive(1);
		}
	}

	//mission mode

	delay(100);
}

void Dataprintln(int mini, int sec, double lat, double lng, double hgt, double Yaw, double GyroZ)
{
	Serial.print(mini);
	Serial.print(":");
	Serial.print(sec);
	Serial.print(" ");
	Serial.print(lat);
	Serial.print(" ");
	Serial.print(lng);
	Serial.print(" ");
	Serial.print(hgt);
	Serial.print(" ");
	Serial.print(Yaw);
	Serial.print(" ");
	Serial.println(GyroZ);
        delay(1000);
}

void Stringprintln(String str)
{
	Serial.println(str);
        delay(1000);
}


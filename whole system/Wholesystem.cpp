//whole system ino code
//2015.07.05 Kwon Hwi Jae
//WIFI.h not yet
//Mission.h not yet
//Camera.h not yet
//Some parameters need test
//skip datasend, store

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

//#include "AltSoftSerial.h"
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//AltSoftSerial ESP8266; // (8,9) RX,TX
//SoftwareSerial GPS_Serial (10,11); //RX,TX

#define goalLat "" //not yet
#define goalLng "" //not yet
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
	delay(2000);

	gps.renew();//consider cold start 
	imu.initiate();
	delay(2000);

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

	Dataprintln("dataform");//data form

	while(flight.getflight()>0)//SAT is flying
	{
		gps.renew(); //consider cold start
		imu.renew();
		int min = minute();
		int sec = second();
		double lat = gps.getLat();
		double lng = gps.getLng();
		double hgt = gps.getHgt();
		double deltaH = gps.getdeltaH();
		//IMU imformation 
		double Roll = imu.getRoll();
   		double Pitch = imu.getPitch();
   		double Yaw = imu.getYaw();
   		double GyroX = imu.getGyroX();
   		double GyroY = imu.getGyroY();
   		double GyroZ = imu.getGyroZ();
   		double AccX = imu.getAccX();
   		double AccY = imu.getAccY();
   		double AccZ = imu.getAccZ();
   		double Tem = imu.getTem(); 
   		Dataprintln(min, sec, lat, lng, hgt, Yaw, GyroZ);
		/*...
		data send
		...*/
		flight.GPScheck1(lat, lng);
		flight.FlightCheck(deltaH);

		if((minute()-startmin)>15) { break;} //flight time limit 15min
	}

	flight.GPScheck2(); //GPS 0,0 check
	errorstate = flight.getGPSError() + flight.getIMUError() + flight.getWIFIError(); //0 : Error, not 0 : not Error
	Serrorstate = flight.getSGPSError() + flight.getSIMUError() + flight.getSWIFIError();
	Dataprintln(Serrorstate); //error state
	if(errorstate!=0) {safe.setsafe(1);} //error --> safemode
	else {waiting.setwaiting(1);} //no error --> waitingmode

	if(waiting.getwaiting()) //waiting mode
	{	
		waiting.heatline(heatpin);//heat line for 10sec
		waiting.setwaiting(0); //waiting mode end
		drive.initiate(goalLat, goalLng); //motor on
		drive.setDrive(1); //drive mode start
	}
}

void loop()
{
	gps.renew();
	imu.renew();
	int min = minute();
	int sec = second();
	double lat = gps.getLat();
	double lng = gps.getLng();
	double hgt = gps.getHgt();
	double deltaH = gps.getdeltaH();
	//IMU imformation 
	double Roll = imu.getRoll();
   	double Pitch = imu.getPitch();
   	double Yaw = imu.getYaw();
   	double GyroX = imu.getGyroX();
   	double GyroY = imu.getGyroY();
   	double GyroZ = imu.getGyroZ();
   	double AccX = imu.getAccX();
   	double AccY = imu.getAccY();
   	double AccZ = imu.getAccZ();
   	double Tem = imu.getTem(); 
   	Dataprintln(min, sec, lat, lng, hgt, Yaw, GyroZ);
   	/*...
	data send --> after drive
	...*/
	
	if(safe.safecheck(lat, lng, wifi.stop()))//safe check
	{
		drive.getDrive(0);
		stuck.getstuck(0);
		drive.stop();
		Stringprintln(safe.getSsafe());
		wifi.Println(safe.getSsafe());
		delay(300000); //1min
	}
	else if(drive.getDrive()>0)//drive mode
	{
		drive.update(lat, lng, Yaw, GyroZ);
		drive.gotoGoal();
		if(stuck.StuckCheck(lat,lng)) //stuck check 
		{
			Stringprintln(stuck.getSstuck());
			wifi.Println(stuck.getSstuck());
			stuck.setstuck(1); 
			drive.stop();
			drive.getDrive(0);
		} 
		//mission condition check --> stop		
	}
	else if(stuck.getstuck()>0)//stuck mode
	{
		drive.stop();
		drive.escape();
		if(stuck.escape(lat, lng))//escape check
		{
			Stringprintln(stuck.getSstuck());
			wifi.Println(stuck.getSstuck());			
			stuck.setstuck(0);
			drive.setDrive(1);
		}
	}

	//mission mode

	delay(1000);
}

void Dataprintln(int min, int sec, double lat, double lng, double hgt, double Yaw, double GyroZ)
{
	Serial.print(min);
	Serial.print(.);
	Serial.print(sec);
	Serial.print(" | ");
	Serial.print(lat,5);
	Serial.print(" | ");
	Serial.print(lng,5);
	Serial.print(" | ");
	Serial.print(hgt,5);
	Serial.print(" | ");
	Serial.print(Roll,5);
	Serial.print(" | ");
	Serial.print(Pitch,5);
	Serial.print(" | ");
	Serial.print(Yaw,5);
	Serial.print(" | ");
	Serial.print(GyroX,5);
	Serial.print(" | ");
	Serial.print(GyroY,5);
	Serial.print(" | ");
	Serial.print(GyroZ,5);
	Serial.print(" | ");
	Serial.print(AccX,5);
	Serial.print(" | ");
	Serial.print(AccY,5);
	Serial.print(" | ");
	Serial.print(AccZ,5);
	Serial.print(" | ");
	Serial.print(Tem,5);
	Serial.println(""); //'\n' --> end;
}

void Stringprintln(String str)
{
	Serial.println(str);
}

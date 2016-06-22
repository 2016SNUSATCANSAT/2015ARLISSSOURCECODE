//Flight cpp file
//2015.06.30
//Kwon Hwi Jae
//2015.07.11 --> ver2

#include "Arduino.h"
#include "Flight.h"

Flight::Flight()
{
	lat = 0;
	lng = 0;
	deltaH = 1000;
	WHO_AM_I = 0;
	STATUS = 0;
	WIFIErrornum1 = 0;
	WIFIErrornum2 = 0;
	GPSError = 0;
	WIFIError = 0;
	IMUError = 0;
	flight = 1;
	String SGPSError = "";
	String SWIFIError = "";
	String SIMUError = "";
}

int Flight::getGPSError() {return GPSError;}
int Flight::getWIFIError() {return WIFIError;}
int Flight::getIMUError() {return IMUError;}
int Flight::getflight() {return flight;}

String Flight::getSGPSError() {return SGPSError;}
String Flight::getSWIFIError() {return SWIFIError;}
String Flight::getSIMUError() {return SIMUError;}

/*void Flight::setlat(double n) { lat = n;}
void Flight::setlng(double n) { lng = n;}
void Flight::sethgt(double n) { hgt = n;}
void Flight::setdeltaH(double n) { deltaH = n;}
void Flight::setWHO_AM_I(double n) { WHO_AM_I = n;}
void Flight::setSTATUS(double n) { STATUS = n;}
void Flight::setWIFIErrornum(int n) { WIFIErrornum = n;}*/

/*void Flight::Flightsystem()
{
	GPScheck1();
	WIFIcheck();
	IMUCheck();
	FlightCheck();
	//if we need, add delay
}*/

void Flight::GPScheck1(double gpslat, double gpslng)
{
	lat = gpslat;
	lng = gpslng;
	if((lat>CheckLat)||(lng>CheckLng))
	{
		GPSError = 1; //Error
		SGPSError = "GPS error1 "; //Error
	}
	else
	{
		GPSError = 0; //no error
		SGPSError = "GPS no error "; //no error
	}
}

void Flight::GPScheck2()
{
	if(!GPSError) //if there's no error in GPScheck1
	{
		if((lat==0)&&(lng==0))
		{
			GPSError = 1; //Error
			SGPSError = "GPS error2 " ;//Error
		}
		else
		{
			GPSError = 0; //no error
			SGPSError = "GPS no error "; //no error
		}
	}
}

void Flight::WIFIcheck(int Errornum1, int Errornum2)
{
	WIFIErrornum1 = Errornum1;
	WIFIErrornum2 = Errornum2;
	if((WIFIErrornum1>CheckWIFI1)||(WIFIErrornum2>CheckWIFI2))
	{
		WIFIError = 1; //Error
		SWIFIError = "WIFI error "; //Error
	}
	else
	{
		WIFIError = 0; //no error
		SWIFIError = "WIFI no error "; //no error
	}
}

void Flight::IMUcheck(double who_am_i, double status)
{
	WHO_AM_I = who_am_i;
	STATUS = status;
	if((WHO_AM_I!=CheckWho_AM_I)||(STATUS!=CheckSTATUS))
	{
		IMUError = 1; //Error
		SIMUError = "IMU error "; //Error
	}
	else
	{
		IMUError = 0; //no error
		SIMUError = "IMU no error "; //no error
	}
}

void Flight::FlightCheck(double gpsdeltaH)
{
	deltaH = gpsdeltaH;
	if(deltaH<deltaHlimit)
	{
		flight = 0;
	}
	else
	{
		flight = 1;
	}
}

//Flight header file
//2015.06.30
//Kwon Hwi Jae
//2015.07.11 --> ver2

#ifndef Filght_h
#define Flight_h

#include "Arduino.h"

#define CheckLat 4000 //not yet
#define CheckLng 13000 //not yet
#define CheckWIFI1 20
#define CheckWIFI2 50
#define CheckSTATUS 128.00 // not yet
#define CheckWho_AM_I 177.00 //not yet
#define deltaHlimit 5 //not yet

class Flight
{
public:
	Flight();
	int getGPSError(); // GPS error : 0, no error : 1
	int getWIFIError(); //WIFI error : 0, no error : 1
	int getIMUError(); // IMU error: 0, no error : 1
	int getflight(); //Flight : 1, not flight : 0
	String getSGPSError(); //GPS error : "GPS error", no error : "GPS no error"
	String getSWIFIError(); //WIFI error : "WIFI error", no error : "WIGI no error"
	String getSIMUError(); //IMU error : "IMU error", no error : "IMU no error"
	void GPScheck1(double gpslat, double gpslng); //GPS error check1, limit
	void GPScheck2(); //GPS error check2, 0.0.0
	void WIFIcheck(int Errornum1, int Errornum2); // WIFI error check
	void IMUcheck(double who_am_i, double status); // IMU error check
	void FlightCheck(double gpsdeltaH); //check flight 
	//void setlat(double n);
	//void setlng(double n);
	//void sethgt(double n);
	//void setdeltaH(double n);
	//void setWIFIErrornum(int n);
	//void setWHO_AM_I(double n);
	//void setSTATUS(double n);
	//void Flightsystem();

private:
	double lat;
	double lng;
	double hgt;
	double deltaH;
	double WHO_AM_I;
	double STATUS;
	int WIFIErrornum1;
	int WIFIErrornum2;
	int GPSError;
	int WIFIError;
	int IMUError;
	int flight;
	String SGPSError;
	String SWIFIError;
	String SIMUError;
};

#endif


//Safe header file
//2015.07.05
//Kwon Hwi Jae
//2015.07.11 --> ver2.0
//2015.08.07 --> ver2.1

#ifndef Safe_h
#define Safe_h

#include "Arduino.h"

#define timelimit 30
#define distancelimit1 100//time and distance
#define distancelimit2 100//just distance
#define stucklimit 10 

class Safe
{
public:
	Safe();
	Safe(double goalLat, double goalLng);
	int getsafe(); //safemode : 1, not safemode : 0
	String getSsafe(); //safemode : "Saftemode", not safemode : "not safemode"
	bool safecheck(double gpslat, double gpslng, bool stopsignal, int stuck);
	//void setlat(double n);
	//void setlng(double n);
	void setsafe(int n);
        void setSsafe(String str);
	void caldistance(double gpslat, double gpslng);

private:
	void safecheck1(); //time, distance
	void safecheck2(); //GPS distance
	void safecheck3(bool stopsignal); //groundstation
	//void safecheck4(); //IMU broken
        void safecheck5(int stuck); //stuck limit
	int safe;
	int nowminute;
	double goallat;
	double goallng;
	double lat;
	double lng;
	double distance;
	String Ssafe;
	//String groundmes;
};

#endif

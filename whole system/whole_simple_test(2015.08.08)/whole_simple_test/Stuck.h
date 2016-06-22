//Safe header file
//2015.07.02
//Kwon Hwi Jae
//2015.07.11 --> ver 2.0
//2015.08.07 --> ver2.1

#ifndef Stuck_h
#define Stuck_h

#include "Arduino.h"

#define stuckcount 10//not yet
#define limescapecount 3 //not yet
#define limitlat 10 //not yet
#define limitlng 10 //not yet

class Stuck
{
public:
	Stuck();
	int getstuck();
	String getSstuck();
	void setstuck(int n);
        void setescapecount(int n);
        int getescapecount();
	bool StuckCheck(double lat, double lng);
	bool escape(double lat, double lng);

private:
	int stuck; //stuck : 1, not stuck : 0
	int count; // stuck check number
        int escapecount;
	String Sstuck;
	double pastlat;
	double pastlng;
	double currentlat;
	double currentlng;
};

#endif

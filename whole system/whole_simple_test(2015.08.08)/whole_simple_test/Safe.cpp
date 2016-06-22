//Safemode cpp file
//2015.07.05
//Kwon Hwi Jae
//2015.07.11 --> ver2.0
//2015.08.07 --> ver2.1

#include "Arduino.h"
#include "Time.h"
#include "Safe.h"


Safe::Safe()
{
	safe = 0;
	Ssafe = "";
	//groundmes = "";
	nowminute = 0;
	goallat = 0;
	goallng = 0;
	lat = 0;
	lng = 0;
	distance = 0;
}

Safe::Safe(double goalLat, double goalLng)
{
	safe = 0;
	Ssafe = "";
	//groundmes = "";
	nowminute = 0;
	goallat = goalLat;
	goallng = goalLng;
	lat = 0;
	lng = 0;
	distance = 0;
}


int Safe::getsafe() {return safe;}
String Safe::getSsafe() {return Ssafe;}

/*void Safe::setlat(double n) {lat = n;}
void Safe::setlng(double n) {lng = n;}*/
void Safe::setsafe(int n) {safe = n;}
void Safe::setSsafe(String str) { Ssafe = str;}

void Safe::caldistance(double gpsLat, double gpsLng)//not yet
{

}

void Safe::safecheck1()
{
	nowminute = minute(); //get current minute
	if(nowminute>=timelimit)
	{
		if(distance > distancelimit1)
		{
			safe = 1; //Be safemode
			Ssafe = "Safe mode1 ";
		}
	}
}

void Safe::safecheck2()
{
	if(distance>distancelimit2)
	{
		safe = 1;
		Ssafe = "Safe mode2 ";
	}
}

void Safe::safecheck3(bool stopsignal)
{
	if(stopsignal)
	{
		safe = 1;
		Ssafe = "Safe mode3";
	}
}

/*void Safe::safecheck4()
{
	
}*/

void Safe::safecheck5(int stuck)
{
	if(stuck >= stucklimit)
        {
             safe = 1;
             Ssafe = "Safe mode5";
        }
}

bool Safe::safecheck(double gpsLat, double gpsLng, bool stopsignal, int stuck)
{
	if(safe) { return true; }
	caldistance(gpsLat, gpsLng);
	safecheck1();
	safecheck2();
	safecheck3(stopsignal);
	//safecheck4();
        safecheck5(stuck);
	if(safe)
	{
		return true;
	}
	return false;
}

//


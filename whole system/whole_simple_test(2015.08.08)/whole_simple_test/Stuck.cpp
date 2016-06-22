//Safemode cpp file
//2015.07.02
//Kwon Hwi Jae
//2015.07.11 --> ver 2.0
//2015.08.07 --> ver2.1

#include "Arduino.h"
#include "Stuck.h"


Stuck::Stuck()
{
	stuck = 0;
	count = 0;
	pastlat = 0;
	pastlng = 0;
	currentlat = 0;
	currentlng = 0;
	Sstuck = "";
        escapecount = 0;
}

int Stuck::getstuck() {return stuck;}
int Stuck::getescapecount() { return escapecount;}
String Stuck::getSstuck() {return Sstuck;}
void Stuck::setstuck(int n) {stuck = n;}
void Stuck::setescapecount(int n) { escapecount = n;}

bool Stuck::StuckCheck(double lat, double lng)
{
	count++;
	currentlat = lat;
	currentlng = lng;
	if(count==1)
	{
		pastlat = lat;
		pastlng = lng;
	}

	if(count == stuckcount)
	{
		if(((currentlat-pastlat)<limitlat)&&((currentlng-pastlng)<limitlng)&&((pastlat-currentlat)<limitlng)&&((pastlng-currentlng)<limitlng))
		{
			stuck = 1;
			count = 0;
			Sstuck = "stuck";
			return true;
		}
		count = 0;
	}
	stuck = 0;
	return false;
}

bool Stuck::escape(double lat, double lng)
{
	count++;
	currentlat = lat;
	currentlng = lng;
	if(count==1)
	{
		pastlat = lat;
		pastlng = lng;
	}
	if(count == limescapecount) //test 
	{
                escapecount++;
		if(((currentlat-pastlat)<limitlat)&&((currentlng-pastlng)<limitlng)&&((pastlat-currentlat)<limitlng)&&((pastlng-currentlng)<limitlng))
		{
			stuck = 1;
			count = 0;
			return false;
		}
		
		stuck = 0;
		count = 0;
		Sstuck = "escape";
		return true;
	}
	return false;
}

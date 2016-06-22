//MAX-6Q I2C header file
//2015.07.14 


#ifndef MAX_h
#define MAX_h

#include "Arduino.h"
#include <Wire.h>

#define ADDRESS 0x42

class MAX
{
public:
  	MAX();
  	int renew();
  	void MAXstart();

 	double getLat();
	double getLng();
  	double getHgt();
  	double getDeltaH();

 	String getSLat();
  	String getSLng();
  	String getSHgt();

  	int count;

private:

 	void BufIn(String &buf);  // Get GPS data from GPS module and store the data into GPSBuf
 	int getPhrase(String &momBuf, String &sonBuf); //Get the phrase that includes longitude and latitude data.
  	String getLat(String Buf);
  	String getLong(String Buf);
  	String getHigh(String Buf);
  	int StoF();
  	int spellCheck(String Buf);
  	void writeRegister8(uint8_t Reg);
  	void readRegister8();
  	char charreadRegister8();

  	uint8_t byte1;
  	uint8_t byte2;
  
  	String GPSBuf; //Whole GPS data buffer
  	String GPSPhr; //GPS phrase buffer
  
  	String fallV; //falling velocity

  	double latitude;
  	double longitude;
  	double height;
  	double deltaH;
  	String sLatitude;
  	String sLongitude;
  	String sHeight;
};

#endif
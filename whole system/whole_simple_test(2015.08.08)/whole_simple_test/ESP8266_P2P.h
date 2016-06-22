//ESP8266_P2P header file
//2015.07.04 Kim Ju Hyun
//2015.07.11 modified by Kwon ver4.0

#ifndef ESP8266_P2P_h
#define ESP8266_P2P_h

#include "Arduino.h"

class ESP8266_P2P{
public:
	ESP8266_P2P();
	void startESP();
	void Print(String m);
	void Print(double m);
	void Println(String m);
	void Println(double m);
	bool stop();
	int geterrornum1();
	int geterrornum2();
	String getReadyIP();

private:
	void clearBuffer();
	void flush();
	int state;//0 = booting, 1 = standby, 2 = Send, 3 = Receive
	int errornum1;
	int errornum2;
	String ReadyIP; //get Ready and IP
};

#endif
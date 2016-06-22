//ESP8266_P2P cpp file
//2015.07.04 Kim Ju Hyun
//2015.07.11 modified by Kwon ver4.0
//2015.08.26 --> drive cal test

#include "ESP8266_P2P2.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10,11); //Rx, Tx

ESP8266_P2P::ESP8266_P2P(){
	state = 0;
	errornum1 = 0;
	errornum2 = 0;
	String ReadyIP = "";
}

int ESP8266_P2P::geterrornum1() { return errornum1;}
int ESP8266_P2P::geterrornum2() { return errornum2;}
String ESP8266_P2P::getReadyIP () {return ReadyIP;}

void ESP8266_P2P::startESP(){
	ESP8266.begin(9600);
	while(errornum1<20)
	{
   // Serial.println("reset.....");  
		errornum1 ++;
		ESP8266.println("AT+RST");
		delay(200);
		if(ESP8266.find("OK"))
		{
			ReadyIP = "Ready\n";
			break;
		}
		else
		{
			
			ReadyIP = "Reset failed\n";
		}
	}
	ESP8266.println("AT+CWMODE=3");
	delay(200);
	while(errornum2<50)
	{
		errornum2++;
		ESP8266.println("AT+CIPMUX=1");
		delay(200);

		if(ESP8266.find("OK"))
		{
			ReadyIP += "Get IP\n";
			break;
		}
	}

	ESP8266.println("AT+CIFSR");
	delay(200);
	while(ESP8266.available())
	{
		char c = ESP8266.read();
		ReadyIP += c;
	}

	ESP8266.println("AT+CIPSERVER=1,1000");
	delay(200);
	state = 1;
}

void ESP8266_P2P::Print(String message)
{
	if(state = 1)
	{
		state = 2;
		clearBuffer();
		ESP8266.println("AT+CIPSEND=0," + String(message.length()));

		if(ESP8266.find(">"))
		{
			ESP8266.println(message);
		
			while(1)
			{
				if(ESP8266.find("SEND OK"))
				{
					state = 1;
					break;
				}
			}
			flush();
		}
		else
		{
			state = 1;
		}
	}
 clearBuffer();
}

void ESP8266_P2P::Print(double mes)
{
	long int a = mes*1000;
	String message = String(a);
	if(state = 1)
	{
		state = 2;
		clearBuffer();
		ESP8266.println("AT+CIPSEND=0," + String(message.length()));

		if(ESP8266.find(">"))
		{
			ESP8266.println(message);
		
			while(1)
			{
				if(ESP8266.find("SEND OK"))
				{
					state = 1;
					break;
				}
			}
			flush();
		}
		else
		{
			state = 1;
		}
	}
 clearBuffer();
}


void ESP8266_P2P::Println(String message)
{
	if(state = 1)
	{
		state = 2;
		clearBuffer();
		ESP8266.println("AT+CIPSEND=0," + String(message.length() + 2));
		
		if(ESP8266.find(">"))
		{
			message += "\n";
			ESP8266.println(message);
		
			while(1)
			{
				if(ESP8266.find("SEND OK"))
				{
					state = 1;
					break;
				}
			}
			flush();
		}
		else
		{
			state = 1;
		}
	}
 clearBuffer();
}

void ESP8266_P2P::Println(double mes)
{
	long int a = mes*1000;
	String message = String(a);
	
	if(state = 1)
	{
		state = 2;
		clearBuffer();
		ESP8266.println("AT+CIPSEND=0," + String(message.length() + 2));
		
		if(ESP8266.find(">"))
		{
			message += "\n";
			ESP8266.println(message);
		
			while(1)
			{
				if(ESP8266.find("SEND OK"))
				{
					state = 1;
					break;
				}
			}
			flush();
		}
		else
		{
			state = 1;
		}
	}
 clearBuffer();
}

bool ESP8266_P2P::stop(){
	if(ESP8266.find("STOP")){
		return true;
	}
	else return false;
}

void ESP8266_P2P::clearBuffer(){
	while(ESP8266.available() > 0){
		ESP8266.read();
	}
}

void ESP8266_P2P::flush(){
	ESP8266.flush();
}

int ESP8266_P2P::setvalue()
{
	if(ESP8266.find("x")) { return 0;}
	else if(ESP8266.find("a")) { return 1;}
	else if(ESP8266.find("b")) { return 2;}
	else if(ESP8266.find("c")) { return 3;}
	else { return 10;}
}

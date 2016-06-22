//Waiting mode header file
//2015.06.30
//Kwon Hwi Jae
//2015.07.11 --> ver2.0

#ifndef Waiting_h
#define Waiting_h

#include "Arduino.h"

class Waiting
{
public:
	Waiting();
	int getwaiting(); // waiting : 1, not waiting : 0
	void setwaiting(int n); 
	void heatline(int heatpin); //heating line for 10 sec 

private:
	int waiting; //state waiting : 1, not waiting : 0
};

#endif
//Waiting mode cpp file
//2015.06.30
//Kwon Hwi Jae
//2015.07.11 --> ver2.0

#include "Arduino.h"
#include "Waiting.h"

Waiting::Waiting()
{
	waiting = 0;
}

int Waiting::getwaiting() {return waiting;}
void Waiting::setwaiting(int n) {waiting = n;}

void Waiting::heatline(int heatpin)
{
	if(waiting == 1)
	{
		pinMode(heatpin, OUTPUT);
		digitalWrite(heatpin, HIGH);
		delay(5000); //5 sec
		digitalWrite(heatpin, LOW);
	}
}

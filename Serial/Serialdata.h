//Serial header file
//2015.06.28
//overload test!

#ifndef Serialdata_h
#define Serialdata_h

#include <cstring>

class Serialdata{
public:
	void SerialWrite(char *data);  // input char[]
	void SerialWrite(double data); // double
	void SerialWrite(int data); // integer

	char* SerialReadchar(); //return char*
	double SerialReaddou(); //double
	int SerialReadint(); // integer

	void DataStore(char *data);  // input char[]
	void DataStore(double data); // double
	void DataStore(int data); // integer

};

#endif

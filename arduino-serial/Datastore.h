//Serial header file
//2015.06.28
//overload test!

#ifndef Datastore_h_
#define Datastore_h_

#include <cstring>
#include <stdio.h>
#include <time.h>
	
	char*  name(char * time);
	void DataStore(char *data, char* logname);  // input char[]
	void DataStore(double data, char* logname); // double
	void DataStore(int data, char* logname);// integer



#endif

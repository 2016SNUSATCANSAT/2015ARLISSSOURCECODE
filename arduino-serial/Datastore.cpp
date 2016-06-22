//Serialdata cpp file
//2015.06.28

#include "Datastore.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <time.h>

char* name(char* time)
{
	 char name[] = "/home/odroid/Log/";
	char type[] = ".txt";
	static char logname[50];
	sprintf(logname, "%s%s%s", name, time, type);	
	return logname;
}

void DataStore(char* data, char* logname)
{
	FILE *file; //Opening device file

	char getdata[100];
	strncpy(getdata, data, sizeof(getdata));

	file = fopen(logname, "a");//file name
	fprintf(file, "%s", getdata); //writing to the file
	fclose(file);
}

void DataStore(double data, char* logname)
{
	FILE *file; //Opening device file

	double getdata = data;

	file = fopen(logname, "a");
	fprintf(file, "%f", getdata); //writing to the file
	fclose(file);
}

void DataStore(int data, char* logname)
{
	FILE *file; //Opening device file

	int getdata = data;

	file = fopen(logname, "a");
	fprintf(file, "%d", getdata); //writing to the file
	fclose(file);
}


	

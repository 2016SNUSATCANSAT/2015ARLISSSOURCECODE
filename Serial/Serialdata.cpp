//Serialdata cpp file
//2015.06.28

#include "Serialdata.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>

void Serialdata::SerialWrite(char* data)
{
	FILE *file; //Opening device file

	char getdata[100];
	strncpy(getdata, data, sizeof(getdata));

	file = fopen("/dev/ttyACM99", "w");
	fprintf(file, "%s", getdata); //writing to the file
	fclose(file);
}

void Serialdata::SerialWrite(double data)
{
	FILE *file; //Opening device file

	double getdata = data;

	file = fopen("/dev/ttyACM99", "w");
	fprintf(file, "%f", getdata); //writing to the file
	fclose(file);
}

void Serialdata::SerialWrite(int data)
{
	FILE *file; //Opening device file

	int getdata = data;

	file = fopen("/dev/ttyACM99", "w");
	fprintf(file, "%d", getdata); //writing to the file
	fclose(file);
}

char* Serialdata::SerialReadchar()
{
	FILE *file;
	char* getdata = (char*)malloc(100*sizeof(char));
	while(1)
	{
		file = fopen("/dev/ttyACM99", "r");
		if(file == NULL) perror("Error opening file");
		else
		{
			if(fgets(getdata, 100, file) != NULL)
			{
				fclose(file);
				break;
			} 
		}
		fclose(file);
	}
	return getdata;
}

double Serialdata::SerialReaddou()
{
	FILE *file;
	double n = 0;
	char* getdata = (char*)malloc(100*sizeof(char));
	while(1)
	{
		file = fopen("/dev/ttyACM99", "r");
		if(file == NULL) perror("Error opening file");
		else
		{
			if(fgets(getdata, 100, file) != NULL)
			{
				fclose(file);
				break;
			} 
		}
		fclose(file);
	}
	n = atof(getdata);
	return n;
}

int Serialdata::SerialReadint()
{
	FILE *file;
	int n = 0;
	char* getdata = (char*)malloc(100*sizeof(char));
	while(1)
	{
		file = fopen("/dev/ttyACM99", "r");
		if(file == NULL) perror("Error opening file");
		else
		{
			if(fgets(getdata, 100, file) != NULL)
			{
				fclose(file);
				break;
			} 
		}
		fclose(file);
	}
	n = atoi(getdata);
	return n;
}

void Serialdata::DataStore(char* data)
{
	FILE *file; //Opening device file

	char getdata[100];
	strncpy(getdata, data, sizeof(getdata));

	file = fopen("datastore.txt", "a");//file name
	fprintf(file, "%s", getdata); //writing to the file
	fclose(file);
}

void Serialdata::DataStore(double data)
{
	FILE *file; //Opening device file

	double getdata = data;

	file = fopen("datastore.txt", "a");
	fprintf(file, "%f", getdata); //writing to the file
	fclose(file);
}

void Serialdata::DataStore(int data)
{
	FILE *file; //Opening device file

	int getdata = data;

	file = fopen("datastore.txt", "a");
	fprintf(file, "%d", getdata); //writing to the file
	fclose(file);
}


	

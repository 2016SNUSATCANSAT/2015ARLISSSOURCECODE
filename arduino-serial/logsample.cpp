#include "arduino-serial-lib.h"
#include "arduino-serial-lib.c"
#include "Datastore.h"
#include "Datastore.cpp"

#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

char* timeToString(struct tm *t);

int main()
{
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	char* time = timeToString(t);
	char* logname = name(time);
	char name[] = "Odroid on\n";
	DataStore(name, logname);
	while(1){
	char data[100]="";
	int fd = serialport_init("/dev/ttyACM99", 9600);
	if(fd != -1)
	{
		int read = serialport_read_until(fd, data, '\n', 100 , 1000);
		if(read != -1)
		{
			printf("%s", data);
		}
	}
	int close = serialport_close(fd);
	DataStore(data,logname);
	
	/*if((data[0] == 'c')&&(data[1] == 'a')&&(data[2] == 'm'))
	{
		int loadkernel = system("./st");
	}*/

	}
	return 0;
}

char* timeToString(struct tm *t)
{
	static char s[20];
	sprintf(s, "%04d_%02d_%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon+1, t-> tm_mday, t-> tm_hour, t-> tm_min, t -> tm_sec);
	return s;
}

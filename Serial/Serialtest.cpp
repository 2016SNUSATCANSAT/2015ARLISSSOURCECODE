#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include "Serialdata.h"
#include "Serialdata.cpp"

Serialdata test;

int main()
{
	while(1)
	{
			char *data = test.SerialReadchar();
			printf("%s", data);
	}
	return 0;
}

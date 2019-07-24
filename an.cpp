#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int main()
{
 	int i = 0;
 	char load[26];
 	while(i < 25)
 	{
 		system("clear");
 		load[i++] = '|';
 		load[i] = '\0';
 
		printf("\n\nLOADING [%-25s]", load);
 		usleep(199900);
 	}
 
 system("clear");
 printf("\n");
}
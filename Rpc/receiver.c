#include "comm.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
 
#define in_size  100
void commprog_1(char *host, char *input)
{
	CLIENT *clnt;
	char * *result_1;
	char * getsecrets_1_arg;
	getsecrets_1_arg = input;
	clnt = clnt_create(host, COMMPROG, COMMVERS, "TCP");
	
	result_1 = getsecrets_1(&getsecrets_1_arg, clnt);
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	clnt_destroy (clnt);
}

int main (int argc, char *argv[])
{
	char *host;
	char *input;
	input = (char*)malloc(sizeof(char)*in_size);		//malloc space for input
	
	if (argc < 2) {
		host = "127.0.0.1";
		printf ("using the default hostname: 127.0.0.1\n");
	}
	else
		host = argv[1];
	while(1)										//infinite loop
	{
		fgets(input, in_size, stdin);							//get users'  input
		if( (strstr(input,"C00L") != NULL) )		//only when input contains "C00L" or "exit" ,do something 
		{
			commprog_1 (host, input);
		}
	}
	
	exit (0);
}

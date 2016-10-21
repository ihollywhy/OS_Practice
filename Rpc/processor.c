#include "comm.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char ** getsecrets_1_svc(char **argp, struct svc_req *rqstp)
{
	static char * result;

	FILE *my_file;   
	char *input = *argp;
	
	my_file = fopen("secrets.out", "a+");
	if(my_file == (FILE *)NULL)
	{
		my_file = fopen("secrets.out", "w");
	}
	int len = (int)strlen(input)-1;
	int Digitlen = 0;
	int i;
	for(i = 0; i < len; i++)
		if(input[i]>='0' && input[i]<='9')
			Digitlen++;
   fprintf(my_file, "input : ");					//format output
   fputs(input, my_file);						//format output
   fprintf(my_file, "Digit Count : %d\n", Digitlen);	//format output
	fclose(my_file);    
	result = *argp;
	return &result;
}


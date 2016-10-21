#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myshell.h"


//For interest: cd func
/*
 *============================================================
 *	name: cd
 *	input: none
 *	output: none
 *	description: this is for cd command, once the cd is called
 *	then change the path according to the path given
 *============================================================
 */
void cd(void)
{
	if(chdir(*(argv+1)) == -1)
		perror("chdir");
	
}


/*
 *============================================================
 *	name: exec
 *	input: none
 *	output: none
 *	description: this part is for basic command
 *============================================================
 */

void exec(void)
{
	//if there is no command, jump out
	if(*command == '\n')
	{
		exit(0);
	}
	//if there is command, execute
	else 
	{			
		if(execvp(command, argv) == -1 )
			printf("%s: COMMAND NOT FOUND!\n", command);	//the command cannot find, print "COMMAND NOT FOUND!"
		exit(0);

	}	
}

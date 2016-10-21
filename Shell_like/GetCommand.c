#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myshell.h"

/*
 *============================================================
 *	name: GetCommond
 *	input: none
 *	output: int
 *	description: Covert the input string to the formation we
 *	can use in exec.c file. Here, string may contain 2 
 *	information, one is command, the other is argv(parameter).
 *	In this func, the string will be stored as command and 
 *	argv. 
 *============================================================
 */

#define max_input 1000 		//the max char number of input

int GetCommand(void)
{
	char inputs[max_input];
	char *token;
	int index = 0;
	fgets(inputs, max_input, stdin);		//get the string from keyboard

	//if there is no input, get '\n', later once exec() find there is no command, then jump out
	if(inputs[0] == '\n')
	{
		*command = '\n';
	}
	//if there is a information, then divided the string according to ' ' and '\n'
	else
	{
		token = strtok(inputs, " \n");
		argv[0] = token;
		while((token = strtok(NULL, " \n")))
		{
			index++;
			argv[index] = token;
		}
		argv[index+1] = '\0';
	
    		command = argv[0];
	}
	return index;
}

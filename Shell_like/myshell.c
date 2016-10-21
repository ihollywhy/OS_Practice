#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "myshell.h"

/////////////////////////IMPORTANT////////////////////////////
/************************main func***************************/
/*******Testing Environment: Ubuntu 14.04 (Linux)************/
/*************make: to generate the executive file***********/
/***************make clean: to clean all files***************/
/*
 *============================================================
 *	name: main
 *	input: none
 *	output: int
 *	description: Here,this shell can achieve basic commands 
 and cd(add for self interest). The myshell.c include main()
 to make everything together. 
 *============================================================
 */

int main()
{

    int status = 0;             //set for parent process to wait child process
    int myexit = 0;             //flag that indicates user want quit
    
    command = malloc(sizeof(char) * max_command);
    argv = malloc(sizeof(char *) * max_command);

    while(!myexit)				//loop forever unless the myexit is true;
    {
        PrintPrompt();			//print prompt for user each loop (go to PrintPrompt.c to see details) 
        GetCommand();           //handle the string get from keybroad for later use (go to GetCommand.c to see details)

        //command is cd then execute cd() (this function is in exec.c)
        if(!strcasecmp(command, "cd"))
        {
            cd();
        }  

        //command is exit then finish
        else if(!strcasecmp(command, "exit"))	
        {
            return 0;				
        }

        else
        {   //process
            pid_t ischild;
            ischild = fork();
            //in father process: wait child 
            if(ischild != 0)
            {
                waitpid(ischild, &status, 0);
            }
            //in child execute commands 
            else
            {
                exec();         //execute basic commands (this function is in exec.c)
            } 
        }
    }

    return 0;
}



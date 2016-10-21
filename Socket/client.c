#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h>  
#include <arpa/inet.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define in_size  100

int main(int argc, char const *argv[])
{
	char* input;										//input pointer  from user input
	input = (char*)malloc(sizeof(char)*in_size);		//malloc space for input

	int client_sockfd;									//client headler
	struct sockaddr_in server_addr;						//set the server information
	server_addr.sin_family = AF_INET;  					//using IP connection mode 	
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//set server IP address
	//"192.168.1.148"
	server_addr.sin_port = htons(8000);							//set server port, is must be same as server.c

	if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)  		//using socket function to create a client headler
    {  
        perror("socket");  										//socket function error print
        return 0;  
    }  

    if(connect(client_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)  //using server information to creat a connetion with server
    {  
        perror("connect");  									//connect function error print
        return 0;  
    }  

    printf("connected to server\n");  							//for test

	const char* C00L = "C00L";									//for identity
	const char* my_exit = "exit";								//for quit

	while(1)													//infinite loop
	{
		fgets(input, in_size, stdin);							//get users'  input
		if( (strstr(input,C00L) != NULL) || (strstr(input,my_exit) != NULL) )		//only when input contains "C00L" or "exit" ,do something 
			send(client_sockfd,input,in_size,0);				//send the input string server, maxinput size is in_size
		if(strstr(input, my_exit) != NULL)						//if the content contains "exit", then quit
			break;
	}
	free(input);                  				//free the mem space of input
	return 0;
}

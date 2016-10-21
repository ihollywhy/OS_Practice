#include <stdio.h>
#include <sys/wait.h>  
#include <sys/types.h> 
#include <pthread.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

#define in_size  100			//max input number

int input_line;					//count the total input line 
int input_char;					//count the total input char

int server_sockfd;				//server headler
int client_sockfd;				//clinet headler

//get the user stop signal and print some information
void user_stop(int sig)
{
	printf("Total lines is %d\n", input_line);
	printf("Total chars is %d\n", input_char);
	//close the socket even interrupt
	close(client_sockfd);		  
    close(server_sockfd); 
	_exit(0);
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, user_stop);   //get the interrupt signal, relocate to the function user_stop() 

	char* input;			//input pointer  from user input
	char * format_str;		//using for file output
	format_str = (char*)malloc(sizeof(char)*20);	//malloc space for format_str
	input = (char*)malloc(sizeof(char)*in_size);	//malloc space for input
	FILE  * my_file;					//file pointer
	my_file = fopen("secrets.out", "w");		//open file named secrets.out
	const char* my_exit = "exit";			//for quit

    struct sockaddr_in server_addr;   		//server address information struct
    struct sockaddr_in remote_addr; 		//clinet address information struct
    int sin_size;  							//information length

    server_addr.sin_family=AF_INET; 		//set to IP connection
    server_addr.sin_addr.s_addr=INADDR_ANY;	//allow to connect with server  
    server_addr.sin_port=htons(8000); 		//set server port

    //create a socket service
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)  
    {    
        perror("socket");  
        return 1;  
    }  
    
    //blind to make sure the service port is available 
    if (bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)  
    {  
        perror("bind");  
        return 1;  
    }  

    //listening: wait for connection, and the max waitlist is 5
    listen(server_sockfd,5); 

    //get the size of information struct
    sin_size=sizeof(struct sockaddr_in);
 
 	//accept a socket connection
    if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)  
    {  
        perror("accept");  
        return 1;  
    }
    //print success information
    printf("accept a client %s\n",inet_ntoa(remote_addr.sin_addr));  

    //initialize the counters
    input_line = 0;
    input_char = 0;
	while(1)												//infinite loop
	{	
		if(recv(client_sockfd,input,in_size,0) > 0)         //if the count changes, the content is refresh
		{	
			if( strstr(input,my_exit) != NULL )				//if the content contains "exit", then quit
				user_stop(0);
			input_line += 1;								//count for the total input line
			fprintf(my_file, "input : ");					//format output
			fputs(input, my_file);							//format output
			input_char += ((int)strlen(input)-1);			//count for the total input char
			fprintf(my_file, "Digit Count : %d\n", (int)strlen(input)-1);	//format output
			fflush(my_file);								//reflush file
			//fputs(format_str, my_file);
			//strlen(input)
		}		
	}
	//free(input);                  		//free the mem space of input
	fclose(my_file); 						//close the file
	//close the connection
	close(client_sockfd);  
    close(server_sockfd);  
	return 0;
}

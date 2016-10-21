#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define in_size  100
struct shm_struct
{
	int count;            		//count the number of write
	char str[in_size];		//the text of input
};

int main(int argc, char const *argv[])
{
	char* input;						//input pointer  from user input
	input = (char*)malloc(sizeof(char)*in_size);		//malloc space for input

	struct shm_struct * my_shm; 				//new struct for shared mem	
	int my_shmid = 0;					//shared mem id
	
	const char* C00L = "C00L";				//for identity
	const char* my_exit = "exit";				//for quit
	
	key_t shmkey = 1213;					//shared mem key
	my_shmid = shmget(shmkey, sizeof(struct shm_struct), 0644|IPC_CREAT);    		//creat a shared mem and get the id
	my_shm =  (struct shm_struct *)shmat(my_shmid, 0, 0);				//using  shared mem id to map the shared mem to real space:my_shm
	my_shm->count = 0;									//initial the count of share mem
	while(1)										//infinite loop
	{
		fgets(input, in_size, stdin);							//get users'  input
		if( (strstr(input,C00L) != NULL) || (strstr(input,my_exit) != NULL) )		//only when input contains "C00L" or "exit" ,do something 
		{
			//printf("%s", input);							//for debug
			my_shm->count++;							//count++ indicate the content has been modified
			strcpy(my_shm->str, input);						// change the shared mem
			//my_shm->str = input;
		}
		if(strstr(input, my_exit) != NULL)						//if the content contains "exit", then quit
			break;
	}
	free(input);                  				//free the mem space of input
	shmdt(my_shm);                 			//detach from the shared mem
	shmctl(my_shmid, IPC_RMID, 0); 		//delete the shared mem
	return 0;
}
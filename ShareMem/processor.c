#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define in_size  100			//max input number
struct shm_struct
{
	int count;            		//count the number of write
	char str[in_size];		//the text of input
};

int main(int argc, char const *argv[])
{
	char* input;			//input pointer  from user input
	char * format_str;		//using for file output
	format_str = (char*)malloc(sizeof(char)*20);	//malloc space for format_str
	input = (char*)malloc(sizeof(char)*in_size);	//malloc space for input
	FILE  * my_file;					//file pointer
	my_file = fopen("secrets.out", "w");		//open file named secrets.out
	//while( !feof(my_file) )
	//	fgets(input, in_size, my_file);

	struct shm_struct *my_shm = NULL; 		//new struct for shared mem
	int my_shmid = 0;				//shared mem id
	int old_count = 0;				//store the old count of struct, using as a flag to indicate the content of shared mem has been changed
	const char* my_exit = "exit";			//for quit

	key_t shmkey = 1213;				//shared mem key
	my_shmid = shmget(shmkey, sizeof(struct shm_struct), 0644|IPC_CREAT);	//creat a shared mem and get the id
	my_shm = (struct shm_struct *)shmat(my_shmid, 0, 0);				//using  shared mem id to map the shared mem to real space:my_shm
	while(1)									//infinite loop
	{
		if(my_shm->count != old_count)                          			//if the count changes, the content is refresh
		{						
			old_count = my_shm->count;					//update the old_count
			input = my_shm->str;						//get the content 
			//printf("%s", input);						//for debug
			if( strstr(input,my_exit) != NULL )				//if the content contains "exit", then quit
				break;
			fprintf(my_file, "input : ");					//format output
			fputs(input, my_file);						//format output
			fprintf(my_file, "Digit Count : %d\n", (int)strlen(input)-1);	//format output
			//fputs(format_str, my_file);
			//strlen(input)
		}		
	}
	//free(input);                  		//free the mem space of input
	shmdt(my_shm);                 		//detach from the shared mem
	fclose(my_file); 				//close the file
	return 0;
}
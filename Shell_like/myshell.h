//for para: global variables 
#define max_command 100                     //define the max length of command
#define max_path 100

char *command;
char **argv;
char path[max_path];

//for func
int PrintPrompt(void);
int GetCommand(void);
void cd(void);
void exec(void);

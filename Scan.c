#include "main.h"

pid_t pid, child_pid = -1;
extern int status;
extern char* external_commands[200];
extern char prompt[100];

//Scanning input 
void scan_input(char *input, char *prompt)
{
    int check_cmnd;
    extract_external_commands(external_commands);
	//register the signal
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);

	while(1)
	{
		//Printing prompt
		printf("\033[32m%s:~$ \033[0m", prompt);  

		//read the input from the user
		scanf("%[^\n]", input);
		getchar();

		if(*input == '\0')
			continue;

		//validate input is PS1 or not
		if(!strncmp(input, "PS1=", 4))
		{
			//check if any space
			if(input[4] != ' ')
			{
				strcpy(prompt, &input[4]);
			}
			else
			{
				printf("PS1: command not found\n");
			}
			memset(input, 0, 25);
			continue;	
		}

		//Get the command from the input
		char *cmd = get_command(input);

		//Get the command type
		int ret = check_command_type(cmd);

		if(ret == BUILTIN)
		{
			execute_internal_commands(input);
		}
		else if(ret == EXTERNAL)
		{
			pid = fork();
			if(pid > 0) //parent
			{
				//while(waitpid(pid, &status, WUNTRACED | WNOHANG) == 0);
				
				waitpid(pid, &status, WUNTRACED);
				pid = 0;
			}
			else if(pid == 0) //child
			{
				child_pid  = pid;
				execute_external_commands(input);
			}

		}
		else
		{
			printf("%s: Command not found\n", input);
		}

		//reset the input string
		memset(input, 0, 25);
	}
}



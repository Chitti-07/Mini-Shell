#include "main.h"

extern int status;
extern sll *head;

void execute_internal_commands(char *commnd) {
    if(strcmp(commnd, "exit") == 0) {
        exit(0);
    }else if (strcmp(commnd, "pwd") == 0) {
        system("pwd");
    }else if(strncmp(commnd, "cd", 2) == 0) {
		int ret = chdir(commnd + 3);
		if(ret == -1) {
			printf("cd: %s: No such file or directory\n", commnd);
		}
	}else if(strncmp(commnd, "echo", 4) == 0) {
		//special variables
		execute_special_cmd(commnd, status);
	}
    else if(strcmp(commnd, "bg") == 0) {
		if(head != NULL) {
			sll *temp = head;	
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			kill(temp->pid, SIGCONT);
			printf("%s &\n", temp->cmd);
			signal(SIGCHLD, signal_handler);
			delete_last(&head);
		}
		else {
			printf("-bash: bg: current: no such job\n");
		}
	}
	else if(strcmp(commnd, "fg") == 0) {
		if(head != NULL) {
			sll *temp = head;
			while(temp->next)
			{
				temp = temp->next;
			}
			kill(temp->pid, SIGCONT);
			printf("%s\n", temp->cmd);
			waitpid(temp->pid, NULL, WUNTRACED);
			delete_last(&head);
		}
		else {
			printf("-bash: fg: current: no such job\n");
		}
	}
	else if(strcmp(commnd, "jobs") == 0) {
		print_list(head);
	}
	else {
		printf("Invalid command\n");
	}
}


void execute_special_cmd(char *input_string, int status) {
	if(strcmp(input_string, "echo $?") == 0) {
		printf("%d\n", WEXITSTATUS(status));
	}
	else if(strcmp(input_string, "echo $$") == 0) {
		printf("%d\n", getpid());
	}
	else if(strcmp(input_string, "echo $SHELL") == 0) {
		system("pwd");
	}
	else {
		printf("Invalid Command.\n");
	}

}
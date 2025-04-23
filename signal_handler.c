#include "main.h"

extern pid_t pid, child_pid;
extern char input_string[100];
extern char prompt[100];

sll *head = NULL;

void signal_handler(int signum)
{
	if(signum == SIGINT)
	{
		if(child_pid != -1)
		{
			kill(pid, SIGINT);
		}
	}

	if(signum == SIGTSTP)
	{
		if(pid != 0)
		{
			insert_last(pid, input_string, &head);
			kill(pid, SIGTSTP);	
		}
	}

	if(signum == SIGCHLD)
	{
		waitpid(-1, NULL, WNOHANG);

	}
}

void insert_last(int pid, char *cmd, sll **head)
{
	sll *node = malloc(sizeof(sll));
	if(node == NULL)
	{
		printf("DMA for Node Fails.\n");
	}

	node->pid = pid;
	strcpy(node->cmd, cmd);
	node->next = NULL;

	if(*head == NULL){
		*head = node;
		return;
	}

	sll *temp = *head;
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = node;

}

void delete_last(sll **head)
{
	if((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
		return ;
	}

	sll *temp = *head, *prev;
	while(temp->next)
	{
		prev = temp;
		temp = temp->next;
	}
	free(temp);
	prev->next = NULL;
}

void print_list(sll *head)
{
	int i = 1;
	while(head)
	{
		printf("[%d] %d Stopped %s\n", i++, head->pid, head->cmd);
		head = head -> next;
	}
}

#include "main.h"

char* external_commands[200];

/*builtin commands */
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
					"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
					"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "fg", "bg", "jobs", NULL};

int externalCmds = 0;
extern sll *head;
//Used to store input 
char input_string[100];

//Prompt
char prompt[100] = "minishell$";

//Main
int main() {

    //Clears the entire display
    system("clear");

    //Scan function
    scan_input(input_string, prompt);
}

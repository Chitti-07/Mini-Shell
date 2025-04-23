#include "main.h"

// Get Command
char *get_command(char *input_string) {

    //Getting the 1st command
    char str[20];
    int i = 0;
    while (input_string[i] != ' ' && input_string[i]) {
        str[i] = input_string[i];
        i++;
    }
    str[i] = '\0';
    //Creating dynamic memory
    char* command = malloc(strlen(str) + 1);
    //Storing the command
    strcpy(command, str);
    return command;
}

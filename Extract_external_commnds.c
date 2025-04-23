#include "main.h"
int status;
extern int externalCmds;
//Extracting the External commands from the external commands file
void extract_external_commands(char **external_commands) {

    //Opening the file
    int fd = open(FILE, O_RDONLY);
    if (fd == -1) {
        printf("failed to open file\n");
        return;
    }
    int ind = 0;
    int bytes; // Used to store the word size
    char buff[50]; // Used to store file data
    char keyword[20]; // Used to store in external_commands
    while ((bytes = read(fd, buff, sizeof(buff) - 1)) > 0) {
        buff[bytes] = '\0';
        for (int i = 0; buff[i]; i++) {
            if (buff[i] == '\n') {
                keyword[ind++] = '\0';
                external_commands[externalCmds] = malloc(strlen(keyword) + 1);
                strcpy(external_commands[externalCmds++], keyword);
                ind = 0;
            }else {
                keyword[ind++] = buff[i];
            }

        }
    }

    // Left over data in buffer
    if (ind > 0) {
        keyword[ind++] = '\0';
        external_commands[externalCmds] = malloc(strlen(keyword) + 1);
        strcpy(external_commands[externalCmds++], keyword);
        ind = 0;
    }
    close(fd);
}
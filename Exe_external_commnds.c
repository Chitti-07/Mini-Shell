#include "main.h"

//Execute extenl command
void execute_external_commands(char *input_string) {
    char input_copy[100];
    // Copy to avoid modifying original
    strcpy(input_copy, input_string); 
    char* Commnds_arr[100];
    int ind = 0;
    int isPipe = 0;

    // Tokenize the copy instead of the original
    char* token = strtok(input_copy, " ");
    while (token) {
        Commnds_arr[ind++] = token;
        token = strtok(NULL, " ");
    }
    Commnds_arr[ind] = NULL;

    // Check for pipe in the tokenized commands
    for (int i = 0; i < ind; i++) {
        if (strcmp(Commnds_arr[i], "|") == 0) {
            isPipe = 1;
            break;
        }
    }

    if (isPipe) {
        npipe(ind, input_string); // Pass original, unmodified input
        exit(0); // Exit child after handling pipes
    }
    execvp(Commnds_arr[0], Commnds_arr);
    perror("execvp");
    exit(1);
}


int validate(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            return 1;
        }
    }
    return 0;
}

void npipe(int argc, char* input_string) {
    char input_copy[100];
    strcpy(input_copy, input_string); // Work with a copy to avoid issues

    char* commandsAdd[50];
    int commandInd[50];
    int ComndCount = 1;
    int ind = 0;
    int ComndsInd = 0;

    commandInd[ComndsInd++] = 0;
    char* token = strtok(input_copy, " ");
    while (token) {
        commandsAdd[ind] = token;
        if (strcmp(commandsAdd[ind], "|") == 0) {
            commandInd[ComndsInd++] = ind + 1;
            commandsAdd[ind] = NULL;
            ComndCount++;
        }
        ind++;
        token = strtok(NULL, " ");
    }
    commandsAdd[ind] = NULL;

    int prev_fd = 0;
    int fd[2];

    for (int i = 0; i < ComndCount; i++) {
        if (i < ComndCount - 1) {
            pipe(fd);
        }

        int ret = fork();
        if (ret == 0) { // Child process
            if (i > 0) {
                dup2(prev_fd, 0); // Redirect stdin from previous command
                close(prev_fd);
            }
            if (i < ComndCount - 1) {
                close(fd[0]); // Close read end
                dup2(fd[1], 1); // Redirect stdout to pipe
                close(fd[1]);
            }
            // Execute the command
            execvp(commandsAdd[commandInd[i]], &commandsAdd[commandInd[i]]);
            perror("execvp");
            exit(1);
        } else { // Parent process
            if (i > 0) {
                close(prev_fd);
            }
            if (i < ComndCount - 1) {
                close(fd[1]); // Close write end
                prev_fd = fd[0]; // Save read end for next command
            }
        }
    }

    // Parent waits for all child processes
    for (int i = 0; i < ComndCount; i++) {
        wait(NULL);
    }
}
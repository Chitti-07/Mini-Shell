#include "main.h"
//Check command type
extern char *builtins[];
extern char* external_commands[200];

int check_command_type(char *command) {

    // Built-in command
    for (int i = 0; builtins[i]; i++) {
        if (strcasestr(builtins[i], command)) {
            return BUILTIN;
        }
    }
    // External Commands
    for (int i = 0; external_commands[i]; i++) {
        if (strcasestr(external_commands[i], command)) {
            return EXTERNAL;
        }
    }
    return NO_COMMAND;
}
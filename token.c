#include <stdio.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

int tokenize(char *input, char **args) {
    int argc = 0;

    // Tokenize input into command and arguments
    char *token = strtok(input, " ");
    while (token != NULL) {
        if (argc >= MAX_ARGS) {
            // Too many arguments
            return -1;
        }
        args[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    return argc;
}
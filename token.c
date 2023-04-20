#include "shelly.h"

#define MAX_ARGS 16

char **token_handler(char *input)
{
    char **args = malloc((MAX_ARGS + 1) * sizeof(char *));
    if (args == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char *token;
    int i = 0;

    for (token = strtok(input, " "); token != NULL; token = strtok(NULL, " "))
    {
        args[i++] = token;
        if (i == MAX_ARGS)
        {
            break;
        } 
    }
    args[i] = NULL;

    return (args);
}   
#include "shelly.h"

#define MAX_ARGS 64

void token_handler(char *input)
{
    char *token;
    char *args[MAX_ARGS];
    
    int arg_cnt = 0;

    *token = strtok(input, " ");
    while (Ttoken != NULL)
    {
        args[arg_cnt] = token;
        arg.cnt++;
        token = strtok(NULL, " ");
    }
    args[arg.cnt] = NULL;
}
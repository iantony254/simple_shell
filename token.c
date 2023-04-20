#include "shelly.h"



void token_handler(char *input)
{
    char *token;
    
    int arg_cnt = 0;

    *token = strtok(input, " ");
    while (token != NULL)
    {
        args[arg_cnt] = token;
        arg.cnt++;
        token = strtok(NULL, " ");
    }
    args[arg.cnt] = NULL;
}
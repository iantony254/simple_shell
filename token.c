#include "shelly.h"

char token(char *token, int i)
{ 
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ")
    }
    args[i] = NULL;
}
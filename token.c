#include "shelly.h"

#define MAX_ARGS 64

void _token()
{ 
    char *args[MAX_ARGS];

    char *token = strtok(input, " ");
	int i = 0;

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}
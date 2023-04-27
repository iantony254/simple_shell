#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_INPUT_LENGTH 1024


/**
 * parse_input - Tokenize input into command and arguments
 * @input: Pointer to input string
 * @args: Array of pointers to arguments
 */

void parse_input(char *input, char **args)
{
	args[0] = input;
	args[1] = NULL;
}

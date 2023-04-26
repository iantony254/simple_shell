#include <stdio.h>
#include <string.h>
#include "shell.h"

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

/**
 * tokenize - Tokenizes a string into an array of arguments.
 * This function takes a string and tokenizes it into separate arguments,
 * which are stored in the given array. The arguments are separated by spaces.
 * If there are too many arguments to fit in the array,
 * this function returns -1.
 *
 * @input: The input string to tokenize.
 * @args: An array to store the resulting arguments.
 *
 * Return:The number of arguments, or -1 if there are too many arguments.
 */

int tokenize(char *input, char **args)
{
	int argc = 0;
	char *token = strtok(input, " ");
	/* Remove comments */
	char *comment = strchr(input, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}

	/*Tokenize input into command and arguments*/
	while (token != NULL)
	{
		if (argc >= MAX_ARGS)
		{
			/*Too many arguments*/
			return (-1);
		}
		args[argc] = token;
		argc++;
		token = strtok(NULL, " ");
	}
	args[argc] = NULL;
	return (argc);
}

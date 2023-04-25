/* #include <stdio.h> */
/* #include <string.h> */

#include "shelly.h"

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

int tokenize(char *input, char **args)
{
	int argc = 0;

	/*Tokenize input into command and arguments*/
	char *token = strtok(input, " ");

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

void tokenize_input(char *input, char **args, int *argc)
{
*argc = tokenize(input, args);
if (*argc == -1)
{
printf("Error: Too many arguments!\n");
}
}

void execute_command(char **args)
{
execvp(args[0], args);
/* If execvp returns, there was an error */
printf("Error: command not found\n");
exit(EXIT_FAILURE);
}

void handle_child_process(char **args)
{
/* Child process */
execute_command(args);
}

void handle_parent_process(pid_t pid)
{
/* Parent process */
int status;
waitpid(pid, &status, 0);
}

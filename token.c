/* #include <stdio.h> */
/* #include <string.h> */

#include "shelly.h"

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

/**
 * tokenize_input - Tokenizes user input and stores the resulting arguments.
 * This function tokenizes the user input string and stores the resulting
 * arguments in the given array. If there are too many arguments to fit in the
 * array, this function prints an error message.
 *
 * @input: The user input string to tokenize.
 * @args: An array to store the resulting arguments.
 * @argc: A pointer to an integer that will be set to the number of arguments.
 */

void tokenize_input(char *input, char **args, int *argc)
{
*argc = tokenize(input, args);
if (*argc == -1)
{
printf("Error: Too many arguments!\n");
}
}

/**
 * execute_command - Executes a command with the given arguments.
 * This function executes the command with the given arguments using the
 * execvp system call. If the command is not found, this function prints an
 * error message and exits with a failure status.
 *
 * @args: An array of arguments, including the command to execute.
 */

void execute_command(char **args)
{
execvp(args[0], args);
/* If execvp returns, there was an error */
printf("Error: command not found\n");
exit(EXIT_FAILURE);
}

/**
 * handle_child_process - Handles the child process after forking.
 * This function is called in the child process after forking. It executes
 * the command with the given arguments using the execute_command function.
 *
 * @args: An array of arguments, including the command to execute.
 */

void handle_child_process(char **args)
{
/* Child process */
execute_command(args);
}

/**
 * handle_parent_process - Handles the parent process after forking.
 * This function is called in the parent process after forking. It waits for
 * the child process to complete using the waitpid system call.
 *
 * @pid: The process ID of the child process.
 */

void handle_parent_process(pid_t pid)
{
/* Parent process */
int status;
waitpid(pid, &status, 0);
}

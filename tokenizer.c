#include <stdio.h>
#include <string.h>
#include "shell.h"

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

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


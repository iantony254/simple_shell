#include "shelly.h"

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

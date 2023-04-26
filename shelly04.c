#include "shelly.h"
#include <sys/wait.h>
#include "token.c"
#include "execute.c"

#define MAX_INPUT_LENGTH 1024

/**
 * handle_exit_command - prints a message and exits the program
 * Return: none
 */

void handle_exit_command(void)
{
printf("Exiting the matrix terminal...\n");
exit(EXIT_SUCCESS);
}

/**
 * handle_env_command - prints the environment variables
 * Return: none
 */

void handle_env_command(void)
{
char **env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
}

/**
 * fork_and_execute - forks the process and executes the given command
 * @args: an array of strings containing the command and its arguments
 *
 * Return: none
 */

void fork_and_execute(char **args)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/*Child process*/
execute_command(args);
}
else
{
/*Parent process*/
int status;
waitpid(pid, &status, 0);
}
}

/**
 * main - the main function that runs the program
 * Return:0 on success, otherwise an error code
 */

int main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[MAX_ARGS + 1];

while (1)
{
/*Display prompt*/
printf("th3_m@tr!x_$: ");
/*Read input from user*/
if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
{
/*Handle end of file condition*/
printf("\n");
break;
}
/* Remove trailing newline character*/
input[strcspn(input, "\n")] = '\0';
/* Check if the input given is the "exit" command */
if (strcmp(input, "exit") == 0)
{
/* Exit The Program */
handle_exit_command();
}
/* Check if the input given is the "env" command */
if (strcmp(input, "env") == 0)
{
/* Print Environment Variables */
handle_env_command();
continue;
}
/*Tokenize input into command and arguments*/
int argc = tokenize(input, args);
if (argc == -1)
{
printf("Error: Too many Arguments!\n");
continue;
}
/*Fork process to execute command*/
fork_and_execute(args);
}
return (0);
}

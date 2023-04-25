#include "shelly.h"
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

/**
 * display_prompt - Display shell prompt
 */

void display_prompt(void)
{
printf("th3_m@tr!x_$ ");
}

/**
 * read_input - Read input from user
 * @input: Pointer to buffer where input will be stored
 */

void read_input(char *input)
{
if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
{
printf("\n");
exit(EXIT_SUCCESS);
}
input[strcspn(input, "\n")] = '\0';
}

/**
 * tokenize_input - Tokenize input into command and arguments
 * @input: Pointer to input string
 * @args: Array of pointers to arguments
 */

void tokenize_input(char *input, char **args)
{
char *token = strtok(input, " ");
int i = 0;
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;
}

/**
 * execute_command - Fork process to execute command
 * @args: Array of pointers to arguments
 */

void execute_command(char **args)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execvp(args[0], args);
printf("Error: command not found\n");
exit(EXIT_FAILURE);
}
else
{
int status;
waitpid(pid, &status, 0);
}
}

/**
 * main - Entry point of the shell program
 *
 * Return:Always (0)
 */

int main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[MAX_ARGS];
while (1)
{
display_prompt();
read_input(input);
tokenize_input(input, args);
execute_command(args);
}
return (0);
}

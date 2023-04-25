#include "shelly.h"
#include <sys/wait.h>
#include "token.c"

#define MAX_INPUT_LENGTH 1024

/**
 * display_prompt- Display the prompt for the user to input command
 */

void display_prompt(void)
{
printf("th3_m@tr!x_$ ");
}

/**
 * execute_command- Execute the command with given arguments
 * @args: list of arguments for the command.
 */

void execute_command(char *args[])
{
execvp(args[0], args);
printf("Error: command not found\n");
exit(EXIT_FAILURE);
}

/**
 * handle_input- Handle user input by tokenizing into command and arguments,
 * forking a new process to execute the command, and waiting for it to finish.
 * @input: the input string from the user
 */

void handle_input(char input[])
{
/* Remove trailing newline character*/
input[strcspn(input, "\n")] = '\0';
/*Tokenize input into command and arguments*/
char *args[MAX_ARGS + 1];
int argc = tokenize(input, args);
if (argc == -1)
{
printf("Error: Too many Arguments!\n");
return;
}
/*Fork process to execute command*/
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
 * main- The main function that reads user input and handles the command.
 * Return:Always (0).
 */

int main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[MAX_ARGS + 1];
while (1)
{
/*Display prompt*/
display_prompt();
/*Read input from user*/
if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
{
/*Handle end of file condition*/
printf("\n");
break;
}
handle_input(input);
}
return (0);
}

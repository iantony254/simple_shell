#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

/**
 * main- entry point of the program.
 *
 * Return:Always (0).
 */
int main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[MAX_ARGS + 1];
int argc;
while (1)
{
display_prompt();
if (!read_input(input))
{
break;
}
if (strcmp(input, "exit") == 0)
{
/* Exit The Program */
printf("Exiting the matrix terminal...\n");
exit(EXIT_SUCCESS);
}
tokenize_input(input, args, &argc);
if (argc != -1)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
handle_child_process(args);
}
else
{
handle_parent_process(pid);
}
}
}
return (0);
}

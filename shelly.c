#include "shelly.h"
/*#include <sys/wait.h>*/
#include "prompt.c"
#include "input.c"
#include "execute.c"
#include "token.c"

#define MAX_INPUT_LENGTH 1024

/**
 * wait_for_child- Waits for the child process,
 * with the given PID to finish.
 * @pid: The process ID of the child process to wait for.
 */

void wait_for_child(pid_t pid)
{
int status;
waitpid(pid, &status, 0);
}

/**
 * main - Entry point of the shell program
 *
 * Return:Always (0)
 */

int main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[2];
pid_t pid; /*Declare variable at the beginning*/
while (1)
{
display_prompt();
if (!read_input(input))
{
break;
}
parse_input(input, args);
pid = fork(); /*assign value to the variable*/
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
wait_for_child(pid);
}
}
return (0);
}

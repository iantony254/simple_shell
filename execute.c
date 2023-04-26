#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

int execute_command(char **args)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		execvp(args[0], args);
		/* If execvp returns, there was an error */
		printf("Error: command not found\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}

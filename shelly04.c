#include "shelly.h"
#include <sys/wait.h>
#include "token.c"
#include "env-environ.c"

#define MAX_INPUT_LENGTH 1024

int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args [MAX_ARGS + 1];

	while (1)
	{
		/*Display prompt*/
		printf("th3_m@tr!x_$ ");

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
			printf("Exiting the matrix terminal...\n");
			exit(EXIT_SUCCESS);
		}

		/*Tokenize input into command and arguments*/
		int argc = tokenize(input, args);
		if (argc == -1)
		{
			printf("Error: Too many Arguments!\n");
			continue;
		}
		
		/* Check if command is the "env" */
		if (strcmp(args[0], "env") == 0)
		{
			/* Call the env built in */
			env_builtin();
			continue;
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
			execvp(args[0], args);
			/*If execvp returns, there was an error*/
			printf("Error: command not found\n");
			exit(EXIT_FAILURE);
			}
		else
		{
			/*Parent process*/
			int status;

			waitpid(pid, &status, 0);
		}
	}
	return (0);
}

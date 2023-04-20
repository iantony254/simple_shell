#include "shelly.h"

int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	

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

		/*Tokenize input into command and arguments*/
		token_handler(input);

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
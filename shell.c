#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10
#define MAX_ARG_LENGTH 1024

int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS + 1];
	int argc;
	int i;
	int status;

	while (1)
	{
		/*Display prompt*/
		display_prompt();

		/*Read input from user*/
		if (!read_input(input))
		{
			break;
		}

		/* Check if user entered "exit" command */
		if (strcmp(args[0], "exit") == 0)
		{
			/* Check if an argument was provided */
			if (argc > 1)
			{
				/* Convert argument to integer and use as exit status */
				int status = atoi(args[1]);
				exit(status);
			}
			else
			{
				/* Use default exit status of 0 */
				exit(0);
			}
		}
		/* Check if the input given is the "exit" command */
		if (strcmp(input, "exit") == 0)
		{
			/* Exit The Program */
			printf("Exiting the matrix terminal...\n");
			exit(EXIT_SUCCESS);
		}

		/*Tokenize input into command and arguments*/
		argc = tokenize(input, args);
		if (argc == -1)
		{
			printf("Error: Too many Arguments!\n");
			continue;
		}

		/* Check if user entered "alias" command */
		/* if (strcmp(args[0], "alias") == 0)*/
		/* { */
		/*	parse_alias_args(argc, args); */
		/*	continue; */
		/* } */

		/* Check if user entered "cd" command */
		if (strcmp(args[0], "cd") == 0)
		{
			/* If no argument is given, change to home directory */
			if (argc == 1)
			{
				char *home_dir = getenv("HOME");
				if (home_dir == NULL)
				{
					fprintf(stderr, "Error: HOME environment variable not set\n");
					continue;
				}
				if (chdir(home_dir) != 0)
				{
					fprintf(stderr, "Error: could not change to home directory\n");
				}
				else
				{
					setenv("PWD", home_dir, 1);
				}
			}
			else if (strcmp(args[1], "-") == 0)
			{
				/* If argument is "-", change to previous directory */
				char *oldpwd = getenv("OLDPWD");
				if (oldpwd == NULL)
				{
					fprintf(stderr, "Error: OLDPWD environment variable not set\n");
					continue;
				}
				printf("%s\n", oldpwd);
				if (chdir(oldpwd) != 0)
				{
					fprintf(stderr, "Error: could not change to previous directory\n");
				}
				else
				{
					char cwd[1024];
					getcwd(cwd, sizeof(cwd));
					setenv("OLDPWD", getenv("PWD"), 1);
					setenv("PWD", cwd, 1);
				}
			}
			else
			{
				/* Otherwise, change to specified directory */
				if (chdir(args[1]) != 0)
				{
					fprintf(stderr, "Error: could not change to directory\n");
				}
				else
				{
					char cwd[1024];
					getcwd(cwd, sizeof(cwd));
					setenv("OLDPWD", getenv("PWD"), 1);
					setenv("PWD", cwd, 1);
				}
			}
			continue;
		}

		/* Check if user entered "setenv" command */
		if (strcmp(args[0], "setenv") == 0)
		{
			/* Check if variable name and value were provided */
			if (argc != 3)
			{
				fprintf(stderr, "Error: invalid syntax. Usage: setenv VARIABLE VALUE\n");
				continue;
			}

			/* Set environment variable */
			if (setenv(args[1], args[2], 1) != 0)
			{
			fprintf(stderr, "Error: failed to set environment variable\n");
			}

			continue;
		}

		/* Check if user entered "unsetenv" command */
		if (strcmp(args[0], "unsetenv") == 0)
		{
			/* Check if variable name was provided */
			if (argc != 2)
			{
				fprintf(stderr, "Error: invalid syntax. Usage: unsetenv VARIABLE\n");
				continue;
			}

			/* Unset environment variable */
			if (unsetenv(args[1]) != 0)
			{
				fprintf(stderr, "Error: failed to unset environment variable\n");
			}

			continue;
		}

		/* Execute command(s) */
		i = 0;
		while (i < argc)
		{
			status = execute_command(&args[i]);

			/* Handle logical operators */
			if (i < argc-1 && strcmp(args[i+1], "&&") == 0)
			{
				if (status != 0)
				{
					break;
				}
			}
			else if (i < argc-1 && strcmp(args[i+1], "||") == 0)
			{
				if (status == 0)
				{
					break;
				}
			}

			i++;
		}
	}

	return (0);
}

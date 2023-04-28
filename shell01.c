#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_COMMAND_LENGTH 50 /* Maximum length of a command */
#define PROMPT "$ "     /*Shell prompt*/

/* Function to read a command from the user*/
char* read_command() {
    char* command = (char*) malloc(sizeof(char) * MAX_COMMAND_LENGTH);
    if (command == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    printf("%s", PROMPT);
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
      if (feof(stdin)) { /* end of file*/
            exit(EXIT_SUCCESS);
        }
      else { /* error */
            perror("Error reading command");
            exit(EXIT_FAILURE);
        }
    }

    return command;
}

int main() {
  while (1) { /* Loop indefinitely*/
        char* command = read_command();
	pid_t pid;

        /* Remove the newline character from the end of the command */
        command[strcspn(command, "\n")] = '\0';

        pid = fork();
        if (pid == -1) { /* error */
            perror("Error forking process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) { /* child process*/
            if (execlp(command, command, (char*) NULL) == -1) {
                printf("%s: command not found\n", command);
                exit(EXIT_FAILURE);
            }
        }
        else { /* parent process */
	  wait(NULL); /* Wait for the child process to terminate */
        }

        free(command);
    }

    return 0;
}

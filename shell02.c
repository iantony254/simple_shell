#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_LENGTH 1024

int main2(void) {
    char command[MAX_LENGTH];
    char *args[MAX_LENGTH];
    char *token;
    int status;
    int i;
    pid_t pid;

    while (1) {
        printf("$");
        fflush(stdout);

        /* Read command line */
        if (!fgets(command, MAX_LENGTH, stdin)) {
            break;
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = 0;

	/* Parse command line into arguments */
        token = strtok(command, " ");
        i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /* Fork process */
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
	  /* Child process */
            if (execvp(args[0], args) == -1) {
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        } else {
	  /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}

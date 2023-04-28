#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"

#define MAX_LENGTH 1024

extern char **environ;

int main1(void) {
    char command[MAX_LENGTH];
    char *args[MAX_LENGTH];
    char *token;
    int status;
    int i;
    pid_t pid;
    char *dir;
    char command_path[MAX_LENGTH];

    while (1) {
        printf("$");
        fflush(stdout);

        /* Read command line */
        if (!fgets(command, MAX_LENGTH, stdin)) {
            break;
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = 0;

        /* Check if user entered "exit" command */
        if (strcmp(command, "exit") == 0) {
            break;
        }

        /* Check if user entered "env" command */
        if (strcmp(command, "env") == 0) {
            /* Loop through environment variables and print each variable */
            char **env = environ;
            while (*env) {
                printf("%s\n", *env);
                env++;
            }
            continue;
        }

        /* Parse command line into arguments */
        token = strtok(command, " ");
        i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /* Check if command exists */
        if (access(args[0], F_OK) == -1) {
            /* Command not found, print error message and continue */
            printf("Command not found\n");
            continue;
        }

        /* Fork process */
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */

            /* Search for command in PATH */
            char *path = getenv("PATH");
            if (path == NULL) {
                perror("getenv failed");
                exit(EXIT_FAILURE);
            }

            dir = strtok(path, ":");

            while (dir != NULL) {
                snprintf(command_path, MAX_LENGTH, "%s/%s", dir, args[0]);
                if (access(command_path, F_OK) == 0) {
                    args[0] = command_path;
                    break;
                }
                dir = strtok(NULL, ":");
            }

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"
#include "command.h"

#define MAX_INPUT_LENGTH 1024

int main(void) {
    char input[MAX_INPUT_LENGTH];
    char *path = getenv("PATH");

    while (1) {
        // Display prompt
        printf("$ ");

        // Read input from user
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            // Handle end of file condition
            printf("\n");
            break;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Parse command and arguments
        char **args = parse_command(input);

        // Execute command
        execute_command(input, path);
    }

    return 0;
}

char **parse_command(char *input) {
    char **args = malloc((MAX_ARGS + 1) * sizeof(char *));
    if (args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token;
    int i = 0;
    for (token = strtok(input, " "); token != NULL; token = strtok(NULL, " ")) {
        args[i++] = token;
        if (i == MAX_ARGS) {
            break;
        }
    }
    args[i] = NULL;

    return args;
}

void execute_command(char *command, char *path) {
    char *args[MAX_INPUT_LENGTH];
    char *token;

    // Tokenize command into arguments
    token = strtok(command, " ");
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;

    // Check if command exists in PATH
    char *path_entry;
    while ((path_entry = strsep(&path, ":")) != NULL) {
        char cmd_path[MAX_INPUT_LENGTH];
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_entry, args[0]);
        if (access(cmd_path, X_OK) == 0) {
            // Command exists in PATH, fork process to execute command
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                execv(cmd_path, args);
                // If execv returns, there was an error
                perror("execv");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                int status;
                waitpid(pid, &status, 0);
                return;
            }
        }
    }

    // Command not found in PATH
    printf("Error: command not found\n");
}

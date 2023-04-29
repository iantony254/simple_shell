#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"

void display_prompt(void) {
    printf("$ ");
}

char* read_input(void) {
    char* line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char** parse_input(char* line) {
    int bufsize = 64, position = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

int execute_command(char** args) {
    pid_t pid, wpid;
    int status;
    char* path = getenv("PATH");
    char* token;
    char* command_path = NULL;

    /* Search for the command in the directories listed in the PATH environment variable*/
    token = strtok(path, ":");
    while (token != NULL) {
        char* temp_path = malloc(strlen(token) + strlen(args[0]) + 2);
        sprintf(temp_path, "%s/%s", token, args[0]);
        if (access(temp_path, X_OK) == 0) {
            command_path = temp_path;
            break;
        }
        free(temp_path);
        token = strtok(NULL, ":");
    }

    if (command_path == NULL) {
      /* Command not found*/
        fprintf(stderr, "Command not found: %s\n", args[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */

        if (execve(command_path, args, NULL) == -1) {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("Error");
    } else {
        /* Parent process */

        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid != -1);
    }

    free(command_path);
    return 1;
}


void free_args(char** args) {
    int i = 0;
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);
}

int main() {
    char *input;
    char **args;
    int status;

    do {
        display_prompt();
        input = read_input();
        args = parse_input(input);
        status = execute_command(args);

        free(input);
        free_args(args);
    } while (status);

    return 0;
}

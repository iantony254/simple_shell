#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "shell.h"

#define TOKEN_DELIM " \t\r\n\a"

void display_prompt2(void) {
    printf("$ ");
}

char* read_input2(void) {
    char* line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char** parse_input2(char* line) {
    int bufsize = 64, position = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while ((token = strchr(line, ' ')) != NULL) {
        token[0] = '\0';
        tokens[position] = line;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        line = token + 1;
    }

    tokens[position] = line;
    position++;

    tokens[position] = NULL;
    return tokens;
}

int execute_command5(char** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process*/
        if (execvp(args[0], args) == -1) {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("Error");
    } else {
        /* Parent process*/
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid != -1);
    }

    return 1;
}

void free_args2(char** args) {
    int i = 0;
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);
}

int main2() {
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"

#define MAX_INPUT_LENGTH 1024

void display_prompt2(void) {
    printf("$ ");
}

int read_input2(char* buffer) {
    int num_chars_read = 0;
    while (num_chars_read < MAX_INPUT_LENGTH) {
        int c = getchar();
        if (c == EOF || c == '\n') {
            buffer[num_chars_read] = '\0';
            return num_chars_read;
        } else {
            buffer[num_chars_read] = c;
            num_chars_read++;
        }
    }
    /*Input too long*/ 
    buffer[MAX_INPUT_LENGTH-1] = '\0';
    return MAX_INPUT_LENGTH-1;
}

int split_input(char* input, char** args, int max_args) {
    int num_args = 0;
    int in_word = 0;
    int i = 0;
    while (input[i] != '\0' && num_args < max_args-1) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            if (in_word) {
                /*End of word*/ 
                in_word = 0;
                num_args++;
            }
            input[i] = '\0';
        } else {
            if (!in_word) {
                /*Start of word*/
                in_word = 1;
                args[num_args] = &input[i];
            }
        }
        i++;
    }
    if (in_word) {
        /* End of last word*/ 
        num_args++;
    }
    args[num_args] = NULL;
    return num_args;
}

int execute_command5(char** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /*Child process*/ 
        if (execve(args[0], args, NULL) == -1) {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /*Error forking*/ 
        perror("Error");
    } else {
        /*Parent process*/ 
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid != -1);
    }
    return 1;
}

int main2() {
    char input[MAX_INPUT_LENGTH];
    char* args[MAX_INPUT_LENGTH/2 + 1]; /*Maximum number of arguments is input length divided by 2*/ 
    int num_args, status;

    do {
        display_prompt();
        num_args = split_input(input, args, MAX_INPUT_LENGTH/2 + 1);
        if (num_args > 0) {
            status = execute_command(args);
        } else {
            status = 1;
        }
    } while (status);

    return 0;
}

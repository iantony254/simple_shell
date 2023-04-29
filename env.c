#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"

extern char **environ;

char* get_path3(char* cmd) {
    char* path = getenv("PATH");
    char* dir = strtok(path, ":");

    while (dir) {
        char* full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    return NULL;
}

int execute_command4(char** args) {
    pid_t pid, wpid;
    int status;

    char* cmd = args[0];
    char* path;

    if(strcmp(cmd, "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(cmd, "env") == 0) {
        /* Print the current environment */
        char** env = environ;
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
        return 1;
    }

    path = get_path(cmd);
    if (!path) {
        printf("%s: Command not found\n", cmd);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        /* Child process*/
        if (execve(path, args, NULL) == -1) {
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
    free(path);
    return 1;
}

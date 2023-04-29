#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

#include "shell.h"

#define MAX_PATH_LEN 4096

char* get_path4(char* cmd) {
    char* path = getenv("PATH");
    char dir[MAX_PATH_LEN];
    int i = 0;
    struct stat sb;
    char full_path[MAX_PATH_LEN];
    while (*path) {
        if (*path == ':') {
            dir[i] = '\0';
            i = 0;
            if (snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd) >= MAX_PATH_LEN) {
                fprintf(stderr, "Error: Path too long\n");
                return NULL;
            }
            if (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR) {
                char* res = malloc(strlen(full_path) + 1);
                strcpy(res, full_path);
                return res;
            }
        } else {
            dir[i++] = *path;
        }
        path++;
    }
    dir[i] = '\0';
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd) >= MAX_PATH_LEN) {
        fprintf(stderr, "Error: Path too long\n");
        return NULL;
    }
    if (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR) {
        char* res = malloc(strlen(full_path) + 1);
        strcpy(res, full_path);
        return res;
    }
    return NULL;
}

int execute_command5(char** args) {
    pid_t pid, wpid;
    int status;

    char* cmd = args[0];
    char* path = get_path4(cmd);
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"

extern char **environ;


#include "shell.h"


int execute_command7(char** args)
{
    pid_t pid, wpid;
    int status;

    char* cmd = args[0];
    char* path;

    if(strcmp(cmd, "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    } 
    else if (strcmp(cmd, "env") == 0) 
    {
        /* Print the current environment */
        char** env = environ;
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
        return (1);
    }
    else if (strcmp(cmd, "setenv") == 0)
    {
        /* Set an environment variable */
        if (args[1] == NULL || args[2] == NULL)
        {
            fprintf(stderr, "setenv: Too few arguments\n");
            return (1);
        }
        if (setenv(args[1], args[2], 1) != 0)
        {
            fprintf(stderr, "setenv: Failed to set environment variable\n");
            return (1);
        }
        return (1);
    }
    else if (strcmp(cmd, "unsetenv") == 0)
    {
        /* Unset an environment variable */
        if (args[1] == NULL)
        {
            fprintf(stderr, "unsetenv: Too few arguments\n");
            return (1);
        }
        if (unsetenv(args[1]) != 0)
        {
            fprintf(stderr, "unsetenv: Failed to unset environment variable\n");
            return (1);
        }
        return (1);
    }

    path = get_path(cmd);
    if (!path)
    {
        printf("%s: Command not found\n", cmd);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process*/
        if (execve(path, args, NULL) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("Error");
    } else
    {
        /* Parent process*/
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid != -1);
    }
    free(path);
    return (1);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"

int execute_command7(char** args)
{
    pid_t pid, wpid;
    int status;

    char* cmd = args[0];
    char* path;

    int logical_operator;
    int i;

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

    logical_operator = 0;  /*0: no logical operator, 1: &&, 2: ||*/
    
    for (i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "&&") == 0)
        {
            logical_operator = 1;
            args[i] = NULL;  /*Split the arguments into two commands*/ 
            break;
        } else if (strcmp(args[i], "||") == 0)
        {
            logical_operator = 2;
            args[i] = NULL;  /*Split the arguments into two commands*/ 
            break;
        }
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
    }
    else
    {
        /* Parent process*/
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid != -1);

        if (logical_operator == 1) {  /*Handle &&*/ 
            if (WEXITSTATUS(status) == 0) {
                /*First command succeeded, execute second command*/ 
                execute_command4(&args[i+1]);
            }
        }
        else if (logical_operator == 2)
        {  /*Handle ||*/ 
            if (WEXITSTATUS(status) != 0) {
                /*First command failed, execute second command*/ 
                execute_command4(&args[i+1]);
            }
        }
    }
    free(path);
    return (1);
}

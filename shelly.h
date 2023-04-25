#ifndef _SHELLY_H_
#define _SHELLY_H_

/*
 * File: shelly.h
 * Desc: Header file containing prototypes for all functions
 *       written in the simple_shell directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int tokenize(char *input, char **args);

void display_prompt(void);
int read_input(char *input);
void tokenize_input(char *input, char **args, int *argc);
void execute_command(char **args);
void handle_child_process(char **args);
void handle_parent_process(pid_t pid);

#endif /* _SHELLY_H_ */

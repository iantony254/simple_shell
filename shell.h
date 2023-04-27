#ifndef MAIN_H
#define MAIN_H

/**
 * File: main.h
 * Auth: Ian Antony
 * Desc: Header file containing prototypes for all functions
 *       used in the simple_shell directory.
 */

extern char **environ;  /* Declare external environ variable */

void display_prompt(void);
int read_input(char *input);
int tokenize(char *input, char **args);
int execute_command(char **args);
void tokenize_input(char *input, char **args, int *argc);
void execute_command(char **args);
void handle_child_process(char **args);
void handle_parent_process(pid_t pid);

void handle_exit_command(void);
void handle_env_command(void);
void fork_and_execute(char **args);

void handle_input(char input[]);
void get_input(char *input);
void parse_input(char *input, char **args);
void wait_for_child(pid_t pid);
/* void print_aliases(void); */
/* void print_alias(char *name); */
/* void set_alias(char *name, char *value); */
/* void parse_alias_args(int argc, char **args); */

#endif

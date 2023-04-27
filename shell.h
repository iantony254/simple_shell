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
void handle_child_process(char **args);
void handle_exit_command(void);
void handle_env_command(void);
void handle_input(char input[]);
void get_input(char *input);
void parse_input(char *input, char **args);
/* void print_aliases(void); */
/* void print_alias(char *name); */
/* void set_alias(char *name, char *value); */
/* void parse_alias_args(int argc, char **args); */

#endif

#ifndef SHELL_H
#define SHELL_H


/* Constants */
#define BUFSIZE 1024
#define TOK_DELIM " \t\r\n\a"

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
int _strlen(char *str);
void free_args(char **args);

void perror(const char *s);
void exit(int status);
char* get_path(char* cmd);

#endif

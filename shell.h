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
int execute_command3(char** args);
char* get_path2(char* cmd);
int execute_command2(char** args);
int execute_command4(char** args);
char* get_path3(char* cmd);
extern char **environ;

char* custom_getline(void);

void display_prompt2(void);
int read_input2(char* buffer);
int split_input(char* input, char** args, int max_args);
int execute_command5(char** args);
int main2();

#endif

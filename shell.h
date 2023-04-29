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

int execute_command5(char** args);
/*char* get_path4(char* cmd);*/

char* get_path5(char* cmd);
int execute_command6(char** args);

char* read_input2(void);
char** parse_input2(char* line);
void free_args2(char** args);
int main2();
void display_prompt2(void);

int execute_command7(char** args);

#endif

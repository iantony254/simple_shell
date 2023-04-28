#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 50
#define PROMPT "$ "
#define MAX_LENGTH 1024

char* read_command();

int main(void);
int main2(void);
int main3(void);
int main4(void);
int main1(void);


int access(const char *pathname, int mode);
char *getenv(const char *name);
pid_t fork(void);
pid_t waitpid(pid_t pid, int *status, int options);
int execvp(const char *file, char *const argv[]);
char *strtok(char *str, const char *delim);
int snprintf(char *str, size_t size, const char *format, ...);
void perror(const char *s);

void remove_newline(char *string);
void parse_command(char *command, char **args);
void search_command(char **args, char *command_path);
void execute_command(char **args, char *command_path);

int access(const char *pathname, int mode);
pid_t fork(void);
char *getenv(const char *name);
pid_t waitpid(pid_t pid, int *status, int options);
int execvp(const char *file, char *const argv[]);
void perror(const char *s);

#endif /*SHELL_H*/

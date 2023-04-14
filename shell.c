/**
 *This implementation reads user input using fgets and removes the trailing newline character using strcspn. 
 *It then forks a child process to execute the command using execlp, which searches for the command in the PATH environment variable and executes it with any arguments passed in as additional parameters. 
 *If execlp fails, it prints an error message using perror and exits the child process with EXIT_FAILURE. 
 *The parent process waits for the child to exit using waitpid and prints any error messages using perror.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CLI_LENGTH 1024

int main(void) {
  char cmd[MAX_CLI_LENGTH];
  int status;

  while (1) {
    // Display prompt and read user input
    printf("#the_matrix$ ");
    if (fgets(cmd, MAX_CLI_LENGTH, stdin) == NULL) {
      printf("\n");
      break; // End of file condition (Ctrl+D)
    }

    // Remove trailing newline character
    cmd[strcspn(cmd, "\n")] = '\0';

    // Fork a child process to execute the command
    pid_t pid = fork();

    if (pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Child process: execute the command
      if (execlp(cmd, cmd, NULL) < 0) {
        perror("execlp");
        exit(EXIT_FAILURE);
      }
    } else {
      // Parent process: wait for child to exit
      do {
        pid_t wpid = waitpid(pid, &status, WUNTRACED);
        if (wpid == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  }

  return EXIT_SUCCESS;
}
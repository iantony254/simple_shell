#include "shell.h"

#define MAX_INPUT_LENGTH 1024

int main(void) {
    char input[MAX_INPUT_LENGTH];
    char *path = getenv("PATH");

    while (1) {
        // Display prompt
        printf("$ ");

        // Read input from user
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL){
            // Handle end of file condition
            printf("\n");
            break;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Execute command
        execute_command(input, path);
    }

    return (0);
}

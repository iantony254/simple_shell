#include "shelly.h"

/**
 * read_input - Reads input from stdin and removes trailing newline character.
 *
 * @input: Pointer to a buffer where the input will be stored.
 *
 * Return: 1 if input was read successfully, 0 otherwise.
 */

int read_input(char *input)
{
if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
{
/* Handle end of file condition */
printf("\n");
return (0);
}
/* Remove trailing newline character */
input[strcspn(input, "\n")] = '\0';
return (1);
}

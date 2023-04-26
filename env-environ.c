#include "shelly.h"

/**
 * main - Entry point of the program.
 * This program implements the env built-in,
 * that prints the current environment.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the command-line arguments.
 *
 * Return:Always 0.
 */

int main(int argc, char *argv[])
{
/*Declare variable at the beginning of the function*/
char **env = environ;
if (argc != 1)
{
/* Invalid Usage */
fprintf(stderr, "Usage: %s\n", argv[0]);
exit(EXIT_FAILURE);
}
 /* Loop through the environment variables */
while (*env != NULL)
{
printf("%s/n", *env);
env++;
}
return (0);
}

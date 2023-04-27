#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"

/**
 * display_prompt - Displays the shell prompt to the user.
 *
 * This function prints the prompt string to the standard output.
 * The prompt string is typically used to indicate to the user that the shell
 * is ready to accept input.
 */

void display_prompt(void)
{
	printf("th3_m@tr!x_$: ");
}

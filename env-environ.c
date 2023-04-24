#include "shelly.h"

void env_builtin(void)
{
	/* Loop through the environment variables and print them */
	char **env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
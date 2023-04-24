#include "shelly.h"

extern char **environ;

int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		/* Invalid Usage */
		fprintf(stderr, "Usage: %s\n", argv [0]);
		exit(EXIT_FAILURE);
	}

	/* Loop through the environment variables */
	char **env = environ;
	while (*env != NULL)
	{
		printf("%s/n", *env);
		env++;
	}

	return (0);
}

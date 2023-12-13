#include "shell.h"

/**
 * ela_execve - a function that executes the commands or arguments
 * passed to it
 * @args: the arguments aor the commands
 *
 * Return: nothing
 */

void ela_execve(char **args)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, NULL) < 0)
		{
			perror("execution failed");
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}


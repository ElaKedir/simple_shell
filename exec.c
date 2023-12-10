#include "shell.h"

/**
 * ela_execve - a function that executes the commandsand creates
 * new process
 * @args: the arguments passed to it
 *
 * Return: none
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

/**
 * ela_strtok - a function that tokenizes the arguments passed to it
 * @buffer: the argument
 * @dlm: the delimeter that separates one argument from the other
 *
 * Return: none
 */

void ela_strtok(char *buffer, char *dlm)
{
	int i = 0;
	char **args = malloc(64 * sizeof(char *));
	char *token = strtok(buffer, dlm);

	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, dlm);
	}
	args[i] = NULL;

	ela_execve(args);
	free(args);
}


#include "shell.h"

/**
 * ela_strtok - a function that tokenizes the arguments passed to it
 * @buffer: the argument
 * @dlm: the delimiter
 *
 * Return: nothing
 */

void ela_strtok(char *buffer, char *dlm)
{
	int i = 0;
	char **args = malloc(64 * sizeof(char *));
	char *tkn = strtok(buffer, dlm), *path = NULL, *j = "command not found\n";

	if (tkn == NULL)
	{
		write(1, j, strlen(j));
		free(args);
		return;
	}
	while (tkn)
	{
		args[i] = tkn;
		i++;
		tkn = strtok(NULL, dlm);
	}
	args[i] = NULL;
	if (handle_exit(args))
	{
		free(path);
		exit(0);
	}
	if (args[0][0] != '/')
	{
		path = handle_path(args[0]);
		if (path)
		{
			args[0] = path;
		}
		else
		{
			write(1, j, strlen(j));
			free(args);
			free(path);
			return;
		}
	}
	ela_execve(args);
	free(args);
	free(path);
}


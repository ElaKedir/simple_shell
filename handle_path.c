#include "shell.h"

/**
 * *handle_path - a function that that handles the path of the executable path
 * @command: the command
 *
 * Return: the path
 */

char *handle_path(char *command)
{
	char *path = NULL;
	char *token, *temp;
	char *env_path = strdup(getenv("PATH"));

	if (!env_path)
	{
		perror("memory allocation error");
		exit(1);
	}

	token = strtok(env_path, ":");
	while (token)
	{
		temp = malloc(strlen(token) + strlen(command) + 2);
		if (!temp)
		{
			perror("memory allocation error");
			exit(1);
		}
		strcpy(temp, token);
		strcat(temp, "/");
		strcat(temp, command);

		if (file_exists(temp))
		{
			path = temp;
			break;
		}
		else
		{
			free(temp);
			token = strtok(NULL, ":");
		}
	}

	free(env_path);
	return (path);
}


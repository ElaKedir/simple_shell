#include "shell.h"

/**
 * ela_line - a function that reads the line from the screen and
 * allocates memory accordingly
 * @buffer: the pointer that stores the line read from stdin
 * @buffsize: the number of characters passed to the function
 *
 * Return: 0 if successful
 */


int ela_line(char **buffer, size_t *buffsize)
{
	ssize_t rd = 0;
	size_t total = 0;
	char *temp = NULL;
	*buffer = malloc(*buffsize * sizeof(char));
	if (!*buffer)
	{
		perror("memory allocation error");
		exit(1);
	}
	while (1)
	{
		rd = read(0, *buffer + total, 1);
		if (rd == -1)
		{
			perror("line reading error");
			exit(1);
		}
		total += rd;
		if (rd == 0 || (*buffer)[total - 1] == '\n')
		{
			break;
		}
		if (total >= *buffsize)
		{
			*buffsize *= 2;
			temp = realloc(*buffer, *buffsize * sizeof(char));
			if (!temp)
			{
				free(*buffer);
				perror("memory allocation error");
				exit(1);
			}
			*buffer = temp;
		}
	}
	(*buffer)[total] = '\0';
	if ((*buffer)[0] == '\n')
		exit(0);
	return (0);
}


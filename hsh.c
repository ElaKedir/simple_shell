#include "shell.h"


/**
 * main - a simple shell main function that executes the
 * command given to it.
 *
 * Return: O if  successful
 */


int main(void)
{
	char *prompt = "#cisfun$ ";
	size_t buffsize = 1024;
	char *buffer = NULL;

	if (isatty(STDIN_FILENO) == 0)
	{
		ela_line(&buffer, &buffsize);
		ela_strtok(buffer, " \n\t");
		free(buffer);
		return (0);
	}

	while (1)
	{
		ela_prompt(&prompt);
		ela_line(&buffer, &buffsize);
		ela_strtok(buffer, " \n\t");
	}

	free(buffer);
	return (0);
}


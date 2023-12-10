#include "shell.h"


/**
 * main - a simple shell main function that executes the
 * command given to it.
 *
 * Return: O if  successful
 */


int main(void)
{
	char *prompt = NULL;
	size_t buffsize = 1024;
	char *buffer = NULL;

	while (1)
	{
		ela_prompt(&prompt);
		ela_line(&buffer, &buffsize);
		ela_strtok(buffer, " \n\t");
	}

	free(buffer);
	return (0);
}


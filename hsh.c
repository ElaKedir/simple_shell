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
	int line_status;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		ela_prompt(&prompt);
		line_status = ela_line(&buffer, &buffsize);
		if (line_status == -1)
		{
			break;
		}
		if (strlen(buffer) > 0)
		{
			ela_strtok(buffer, " \n\t");
		}
		free(buffer);
		buffer = NULL;
	}

	return (0);
}


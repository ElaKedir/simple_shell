#include "shell.h"

/**
 * handle_exit - a function that handles the exit from the program
 * @args: the argument passed to it to be checked if it is exit
 *
 * Return: false if it is exit
 */

bool handle_exit(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (true);

		if (args[1] != NULL)
		{
			write(1, "Warning: arguments after 'exit' ignored.\n", 40);
		}
		exit(0);
	}
	return (false);
}


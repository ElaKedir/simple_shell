#include "shell.h"

/**
 * file_exists - A function that checks if a file exists and is readable
 * using the access() function
 * @filename: the command that will be checked
 *
 * Return: true if it exists and false if it does not
 */

bool file_exists(char *filename)
{
	if (access(filename, F_OK | R_OK) == 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}


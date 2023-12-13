#include "shell.h"

/**
 * handle_sigint - handles the signal coming from EOF
 * @sig: the signal
 *
 * Return: nothing
 */

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nExiting...\n", 12);
	exit(0);
}


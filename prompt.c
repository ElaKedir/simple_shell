#include "shell.h"

/**
 * ela_prompt - a function that prints the prompt symbo on
 * the screen.
 * @prompt: the prompt characters
 *
 * Return: none
 */

void ela_prompt(char **prompt)
{
	if ((write(1, *prompt, strlen(*prompt))) == -1)
	{
		perror("prompt writing error");
		exit(1);
	}
}


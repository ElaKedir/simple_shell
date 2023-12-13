#include "shell.h"

/**
 * ela_environ - A function that prints the current environment
 * @info: A structure that contains arguments to be used in functions its
 * purpose is to maintain  a constant function prototype.
 *
 * Return: Always 0
 */
int ela_environ(ela_info *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * ela_getenv - A function that gets the value of an environmental variable
 * @info: A structure that contains arguments to be used in functions
 * its purpose is to maintain  a constant function prototype.
 * @name: env var name
 *
 * Return: the value
 */

char *ela_getenv(ela_info *info, const char *name)
{
	list_t *n = info->env;
	char *q;

	while (n != NULL)
	{
		q = starts_with(n->str, name);
		if (q && *q)
			return (q);
		n = n->next;
	}
	return (NULL);
}

/**
 * elaela__setenv - A function that initializes a new environment variable,
 * or modify an existing one
 * @info: A structure that contains arguments to be used in functions
 * its purpose is to maintain  a constant function prototype.
 *
 * Return: Always 0
 */
int elaela__setenv(ela_info *info)
{
	if (info->argc != 3)
	{
		e_puts("The number of parameters provided is not correct\n");
		return (1);
	}
	if (ela__setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * elaela_unsetenv - A function that removes an environment variable
 * @info: A structure that contains arguments to be used in functions
 * its purpose is to maintain  a constant function prototype.
 *
 * Return: Always 0
 */

int elaela_unsetenv(ela_info *info)
{
	int i;

	if (info->argc == 1)
	{
		e_puts("not enough arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		ela_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_envlist - A function that populates env linked list
 * @info: A structure that contains arguments to be used in functions
 * its purpose is to maintain  a constant function prototype.
 *
 * Return: Always 0
 */

int populate_envlist(ela_info *info)
{
	list_t *n = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		ela_add_node_end(&n, environ[j], 0);
	info->env = n;
	return (0);
}

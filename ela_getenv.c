#include "shell.h"

/**
 * ela_get_env -A function that returns the string array copy of our environ
 * @info: a structure that holds arguments to be used in functions to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

char **ela_get_env(ela_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * ela_unsetenv - A function that removes an environment variable
 * @info: a structure that holds arguments to be used in functions
 * @var: the string env var property
 *
 * Return: 1 on delete, 0 otherwise
 */

int ela_unsetenv(ela_info *info, char *var)
{
	list_t *n = info->env;
	size_t j = 0;
	char *ptr;

	if (!n || !var)
		return (0);

	while (n)
	{
		ptr = starts_with(n->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * ela__setenv - A function that initializes a new environment variable,
 * or modify an existing one
 * @info: a structure that holds arguments to be used in functions
 * @var: the string env var property
 * @value: the string env var value
 *
 * Return: Always 0
 */

int ela__setenv(ela_info *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *n;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	n = info->env;
	while (n)
	{
		ptr = starts_with(n->str, var);
		if (ptr && *ptr == '=')
		{
			free(n->str);
			n->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	ela_add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

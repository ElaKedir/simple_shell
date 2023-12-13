#include "shell.h"

/**
 * ela_history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments that will be used in
 * functions its purpose is to maintain constant function prototype.
 *
 * Return: Always 0
 */

int ela_history(ela_info *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unalias - unsets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unalias(ela_info *info, char *str)
{
	char *i, c;
	int ret;

	i = ela__strchr(str, '=');
	if (!i)
		return (1);
	c = *i;
	*i = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*i = c;
	return (ret);
}

/**
 * alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias(ela_info *info, char *str)
{
	char *i;

	i = ela__strchr(str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (unalias(info, str));

	unalias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * write_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int write_alias(list_t *node)
{
	char *i = NULL, *a = NULL;

	if (node)
	{
		i = ela__strchr(node->str, '=');
		for (a = node->str; a <= i; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(i + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ela_alias - mimics the builtin alias
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int ela_alias(ela_info *info)
{
	int i = 0;
	char *j = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			write_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		j = ela__strchr(info->argv[i], '=');
		if (j)
			alias(info, info->argv[i]);
		else
			write_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

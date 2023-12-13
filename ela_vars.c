#include "shell.h"

/**
 * ela_is_chain - A function that tests if the current char in the
 * buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ela_is_chain(ela_info *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * ela_check_chain - A function that checks if we should continue
 * chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void ela_check_chain(ela_info *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * ela_replace_alias - A function that replaces an aliases in the
 * tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ela_replace_alias(ela_info *info)
{
	int j = 0;
	list_t *n;
	char *p;

	while (j < 10)
	{
		n = node_starts_with(info->alias, info->argv[0], '=');
		if (!n)
			return (0);
		free(info->argv[0]);
		p = ela__strchr(n->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
		j++;
	}
	return (1);
}

/**
 * ela_replace_vars - A function that replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int ela_replace_vars(ela_info *info)
{
	int i = 0;
	list_t *n;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			ela_replace_string(&(info->argv[i]),
				_strdup(_itoa(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			ela_replace_string(&(info->argv[i]),
				_strdup(_itoa(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(info->env, &info->argv[i][1], '=');
		if (n)
		{
			ela_replace_string(&(info->argv[i]),
				_strdup(ela__strchr(n->str, '=') + 1));
			continue;
		}
		ela_replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * ela_replace_string - A function that replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int ela_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

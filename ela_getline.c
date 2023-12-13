#include "shell.h"

/**
 * input_buf - buffers commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(ela_info *info, char **buf, size_t *len)
{
	ssize_t rd = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buf, &len_p, stdin);
#else
		rd = _getline(info, buf, &len_p);
#endif
		if (rd > 0)
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0';
				rd--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = rd;
				info->cmd_buf = buf;
			}
		}
	}
	return (rd);
}

/**
 * get_input - A function that gets a line without newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(ela_info *info)
{
	static char *buf;
	static size_t q, j, len;
	ssize_t rd = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rd = input_buf(info, &buf, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		j = q;
		p = buf + q;

		ela_check_chain(info, buf, &j, q, len);
		while (j < len)
		{
			if (ela_is_chain(info, buf, &j))
				break;
			j++;
		}

		q = j + 1;
		if (q >= len)
		{
			q = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (rd);
}

/**
 * read_buf - A function that reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(ela_info *info, char *buf, size_t *i)
{
	ssize_t rd = 0;

	if (*i != '\0')
		return (0);
	rd = read(info->readfd, buf, READ_BUF_SIZE);
	if (rd >= 0)
		*i = rd;
	return (rd);
}

/**
 * _getline - A function that gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(ela_info *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = ela__strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		ela_strncat(new_p, buf + i, k - i);
	else
		ela__strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - A function that blocks ctrl-C from exiting the program
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

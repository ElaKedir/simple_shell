#include "shell.h"

/**
 * obtain_history_file - A function that gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *obtain_history_file(ela_info *info)
{
	char *buff, *directory;

	directory = ela_getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, directory);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * print_history - A function that creates a file or appends to
 * an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int print_history(ela_info *info)
{
	ssize_t fd;
	char *filename = obtain_history_file(info);
	list_t *n = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (n = info->history; n; n = n->next)
	{
		put_fds(n->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - A function that reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(ela_info *info)
{
	int i, z = 0, l_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = obtain_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + z, l_count++);
			z = i + 1;
		}
	if (z != i)
		build_history_list(info, buf + z, l_count++);
	free(buf);
	info->histcount = l_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - A function that adds an entry to a history linked-list
 * @info: parameter struct
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(ela_info *info, char *buf, int linecount)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	add_node_end(&n, buf, linecount);

	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumber_history - A function that renumbers the history linked list after
 * changes
 * @info: parameter struct
 *
 * Return: the new histcount
 */
int renumber_history(ela_info *info)
{
	list_t *n = info->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (info->histcount = i);
}

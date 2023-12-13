#include "shell.h"

/**
 *e_puts - A function that prints an input string
 * @str: the string
 *
 * Return: Nothing
 */
void e_puts(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
	{
		error_putchar(str[i]);
	}
}

/**
 * error_putchar - A function that writes the character c to stderr
 * @c: The character
 *
 * Return: On success 1 and on error -1.
 */

int error_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_fd - A function that writes the character c to a file descriptor
 * @c: The character
 * @fd: The file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *put_fds - A function that prints an input string into a file descriptor
 * @str: the string
 * @fd: the file descriptor
 *
 * Return: the number of characters printed
 */

int put_fds(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}

#include "shell.h"

/**
 * er_stoi - A function that converts a string to an integer
 * @s: the string
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */

int er_stoi(char *s)
{
	int j = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;
	while (s[j] != '\0')
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			output *= 10;
			output += (s[j] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
	j++;
}

/**
 * print_err - A function that prints an error message
 * @info: the parameter & return info struct
 * @estr: the string containing the specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */

void print_err(ela_info *info, char *estr)
{
	e_puts(info->fname);
	e_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(info->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * print_decimal - A function that prints a decimal (integer)
 * @input: the input
 * @fd: the filedescriptor
 *
 * Return: the number of characters printed
 */

int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, i = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		i++;
	}
	else
		_abs_ = input;
	current = _abs_;
	j = 1000000000;
	while (j > 1)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			i++;
		}
		current %= j;
		j /= 10;
	}
	__putchar('0' + current);
	i++;

	return (i);
}

/**
 * _itoa - A function coverts numbers to strings and mimics itoa
 * @num: number
 * @base: base
 * @flags: flags
 *
 * Return: string
 */

char *_itoa(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int j = 0;

	for (j = 0; buf[j] != '\0'; j++)
	{
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
	}
}

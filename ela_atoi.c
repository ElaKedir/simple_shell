#include "shell.h"

/**
 * from_pipe - A function that returns true if shell is from_pipe
 * @info: struct address
 *
 * Return: 1 if it is interactive, 0 otherwise
 */
int from_pipe(ela_info *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_dlmtr - A function that checks if character is a delimeter
 * @c: the character to check
 * @delim: the delimeter
 *
 * Return: 1 if true, 0 if false
 */
int is_dlmtr(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			return (1);
		}
	else
		return (0);
}

/**
 * _atoi - A function that converts strings to integer
 * @s: the string
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0, output;
	unsigned int result = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
		i++;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

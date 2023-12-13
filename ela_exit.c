#include "shell.h"

/**
 *ela__strncpy - A function that copies a string and mimics strncpy
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *
 *Return: the concatenated string
 */
char *ela__strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
	{
		dest[i] = src[i];
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 *ela_strncat - A function that concatenates two strings, mimics concat,
 *@dest: first string
 *@src: second string
 *@n: the amount of bytes to be maximally used
 *
 *Return: the concatenated string
 */

char *ela_strncat(char *dest, char *src, int n)
{
	int i = 0, j = 0;
	char *string = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (string);
}

/**
 *ela__strchr - A functiion that locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *
 *Return: (s) a pointer to the memory area s
 */

char *ela__strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

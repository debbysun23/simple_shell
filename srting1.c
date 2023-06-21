#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int in = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[in])
	{
		dest[in] = src[in];
		in++;
	}
	dest[in] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	char *rt;
	int lnth = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lnth++;
	ret = malloc(sizeof(char) * (lnth + 1));
	if (!rt)
		return (NULL);
	for (lnth++; lnth--;)
		rt[lnth] = *--str;
	return (rt);
}

/**
 *  _puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int it;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, it);
		it = 0;
	}
	if (c != BUF_FLUSH)
		buf[it++] = c;
	return (1);
}

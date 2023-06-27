#include "shell.h"

/**
 **_strncat - concatenates two strings together
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string thst has been concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
	int a;
	int b;
	char *h = dest;

	b = 0;
	a = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (h);
}

/**
 **_strncpy - copies a string thats inputed
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a;
	int b;
	char *t = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (t);
}



/**
 **_strchr - finds a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

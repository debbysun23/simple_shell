#include "shell.h"

/**
 **_strncpy - copy a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int t, j;
	char *s = dest;

	t = 0;
	while (src[t] != '\0' && t < n - 1)
	{
		dest[t] = src[t];
		t++;
	}
	if (t < n)
	{
		j = t;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, p;
	char *s = dest;

	a = 0;
	p = 0;
	while (dest[a] != '\0')
		a++;
	while (src[p] != '\0' && p < n)
	{
		dest[a] = src[p];
		a++;
		p++;
	}
	if (p < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}


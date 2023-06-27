#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int in, j;
	int kl;
	int m;
	int nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (in = 0; str[in] != '\0'; in++)
		if (!is_delim(str[in], d) && (is_delim(str[in + 1], d) || !str[in + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, j = 0; j < nwords; j++)
	{
		while (is_delim(str[in], d))
			in++;
		kl = 0;
		while (!is_delim(str[in + kl], d) && str[in + kl])
			kl++;
		s[j] = malloc((kl + 1) * sizeof(char));
		if (!s[j])
		{
			for (kl = 0; kl < j; kl++)
				free(s[kl]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < kl; m++)
			s[j][m] = str[in++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char d)
{
	int in;
	int j;
	int kl;
	int m;
	int nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (in = 0; str[in] != '\0'; in++)
		if ((str[in] != d && str[in + 1] == d) ||
				    (str[in] != d && !str[in + 1]) || str[in + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, j = 0; j < nwords; j++)
	{
		while (str[in] == d && str[in] != d)
			in++;
		kl = 0;
		while (str[in + kl] != d && str[in + kl] && str[in + kl] != d)
			kl++;
		s[j] = malloc((kl + 1) * sizeof(char));
		if (!s[j])
		{
			for (kl = 0; kl < j; kl++)
				free(s[kl]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < kl; m++)
			s[j][m] = str[in++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

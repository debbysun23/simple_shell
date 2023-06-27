#include "shell.h"

/**
 * interactive - finds out if shell is inteeractive
 * and returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if shell is interactive mode, or 0 otherwise
 */


int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - finds out if character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checksif their is an alphabetic character
 * @c: inputed character
 * Return: 1 if characterb is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to an integer
 * @s: the string that is to be converted
 * Return: 0 if their are no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	unsigned int r = 0;
	int a;
	int sn = 1;
	int fg = 0;
	int outpt;

	for (a = 0; s[a] != '\0' && fg != 2; a++)
	{
		if (s[a] == '-')
			sn *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			fg = 1;
			r *= 10;
			r += (s[a] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sn == -1)
		outpt = -r;
	else
		outpt = r;

	return (outpt);
}

#include "shell.h"

/**
 * _erratoi - converts string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int _erratoi(char *s)
{
	int a = 0;
	unsigned long int rt = 0;

	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			rt *= 10;
			rt += (s[a] - '0');
			if (rt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rt);
}

/**
 * print_error - prints an error message if anything is wrong
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */


void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function that prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a;
	int cnt = 0;
	unsigned int _ab;
	unsigned int crent;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_ab = -input;
		__putchar('-');
		cnt++;
	}
	else
		_ab = input;
	crent = _ab;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_ab / a)
		{
			__putchar('0' + crent / a);
			cnt++;
		}
		crent %= a;
	}
	__putchar('0' + crent);
	cnt++;

	return (cnt);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sn = 0;
	char *pt;
	unsigned long t = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		t = -num;
		sn = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do	{
		*--pt = arr[t % base];
		t /= base;
	} while (t != 0);

	if (sn)
		*--pt = sn;
	return (pt);
}

/**
 * remove_comments - function that replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int b;

	for (b = 0; buf[b] != '\0'; b++)
		if (buf[b] == '#' && (!b || buf[b - 1] == ' '))
		{
			buf[b] = '\0';
			break;
		}
}

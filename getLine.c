#include "shell.h"

/**
 * input_buf - buffers chainedof  commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t lnp = 0;
	ssize_t ar = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		ar = getline(buf, &lnp, stdin);
#else
		ar = _getline(info, buf, &lnp);
#endif
		if (ar > 0)
		{
			if ((*buf)[ar - 1] == '\n')
			{
				(*buf)[ar - 1] = '\0';
				ar--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = ar;
				info->cmd_buf = buf;
			}
		}
	}
	return (ar);
}

/**
 * get_input - gets inputof a line by minus the newline
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static size_t a;
	static size_t b, len;
	static char *buf;
	ssize_t ar = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	ar = input_buf(info, &buf, &len);
	if (ar == -1)
		return (-1);
	if (len)
	{
		b = a;
		p = buf + a;

		check_chain(info, buf, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (ar); 
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: the size number
 */


ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t ar = 0;

	if (*i)
		return (0);
	ar = read(info->readfd, buf, READ_BUF_SIZE);
	if (ar >= 0)
		*i = ar;
	return (ar);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static size_t d, leb;
	size_t k;
	ssize_t ar = 0, s = 0;
	static char buf[READ_BUF_SIZE];
	char *p = NULL, *np = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (d == leb)
		d = leb = 0;

	ar = read_buf(info, buf, &leb);
	if (ar == -1 || (ar == 0 && leb == 0))
		return (-1);

	c = _strchr(buf + d, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : leb;
	np = _realloc(p, s, s ? s + k : k + 1);
	if (!np)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(np, buf + d, k - d);
	else
		_strncpy(np, buf + d, k - d + 1);

	s += k - d;
	d = k;
	p = np;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"

/**
 * is_chain - test if the  current character in
 * the buffer is a chain delimeter.
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if it is a chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - checks if you should continue
 * chaining based on the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in the buffer.
 * @i: starting position in buffer.
 * @len: length of buffer.
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias - replaces any aliases in a tokenized string.
 * @info: the parameter struct
 * Return: 1 if it is replaced or 0 otherwise
 */
int replace_alias(info_t *info)
{
	int a;
	char *p;
	list_t *nd;

	for (a = 0; a < 10; a++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		p = _strchr(nd->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces the vars in a tokenized string.
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */


int replace_vars(info_t *info)
{
	int a = 0;
	list_t *nd;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		nd = node_starts_with(info->env, &info->argv[a][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[a]),
					_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces a string.
 * @old: address the of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */


int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

#include "shell.h"

/**
 * _myhistory - displays the history by line.
 * @info: Structure arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	int r;
	char *po;
	char c;

	po = _strchr(str, '=');
	if (!po)
		return (1);
	c = *po;
	*po = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*po = c;
	return (r);
}

/**
 * set_alias - sets an alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *po;

	po = _strchr(str, '=');
	if (!po)
		return (1);
	if (!*++po)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias of a string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *po = NULL;
	char *ba = NULL;

	if (node)
	{
		po = _strchr(node->str, '=');
		for (ba = node->str; ba <= po; ba++)
		_putchar(*ba);
		_putchar('\'');
		_puts(po + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - similar to the alias builtin.
 * @info: Structure arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	list_t *nd = NULL;
	int a = 0;
	char *po = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;
		while (nd)
		{
			print_alias(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		po = _strchr(info->argv[a], '=');
		if (po)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}

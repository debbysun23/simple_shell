#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *nd = info->env;
	char *pm;

	while (nd)
	{
		pm = starts_with(nd->str, name);
		if (pm && *pm)
			return (pm);
		nd = nd->next;
	}
	return (NULL);
}


/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * _mysetenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int in;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (in = 1; in <= info->argc; in++)
		_unsetenv(info, info->argv[in]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&nd, environ[a], 0);
	info->env = nd;
	return (0);
}

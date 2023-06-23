#include "shell.h"

/**
 * hsh - the main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error,code error.
 */

int hsh(info_t *info, char **av)
{
	int builtin_ret = 0;
	ssize_t rh = 0;

	while (rh != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rh = get_input(info);
		if (rh != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a comand that is builtin
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin is executed successfully,
 * 1 if builtin is found but not successful,
 * 2 if the builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int a;
	int built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command that is in PATH
 * @info: the parameter & return info struct
 * Return: void(no parameter)
 */


void find_cmd(info_t *info)
{
	int a;
	int j;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, j = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an executive thread to run comand
 * @info: the parameter & return info struct
 * Return: void(no parameter)
 */
void fork_cmd(info_t *info)
{
	pid_t child_p;

	child_p = fork();
	if (child_p == -1)
	{
		perror("Error:");
		return;
	}
	if (child_p == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

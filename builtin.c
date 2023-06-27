#include "shell.h"

/**
 * _myexit - closes the shell
 * @info:  arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 */


int _myexit(info_t *info)
{
	int exitch;

	if (info->argv[1])
	{
		exitch = _erratoi(info->argv[1]);
		if (exitch == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the directory of the processthat is being.
 * @info: Structure arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	int chdirn;
	char *si, *dirn, buffer[1024];

	si = getcwd(buffer, 1024);
	if (!si)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirn = _getenv(info, "HOME=");
		if (!dirn)
			chdirn =
				chdir((dirn = _getenv(info, "PWD=")) ? dirn : "/");
		else
			chdirn = chdir(dirn);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(si);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirn =
			chdir((dirn = _getenv(info, "OLDPWD=")) ? dirn : "/");
	}
	else
		chdirn = chdir(info->argv[1]);
	if (chdirn == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the directory of the current process
 * @info: structured arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */


int _myhelp(info_t *info)
{
	char **argarr;

	argarr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argarr); /* temp att_unused workaround */
	return (0);
}

#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buffer;
	char *direction;

	direction = _getenv(info, "HOME=");

	if (!direction)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(direction) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;

	_strcpy(buffer, direction);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, otherwisw -1
 */

int write_history(info_t *info)
{
	list_t *nd = NULL;
	ssize_t fold;
	char *fname = get_history_file(info);

	if (!fname)
		return (-1);

	fold = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fold == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fold);
		_putfd('\n', fold);
	}
	_putfd(BUF_FLUSH, fold);
	close(fold);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
	int in;
	int lst = 0, lcount = 0;
	struct stat st;
	ssize_t fold, rdlen, flsize = 0;
	char *buffer = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);

	fold = open(fname, O_RDONLY);
	free(fname);
	if (fold == -1)
		return (0);
	if (!fstat(fold, &st))
		flsize = st.st_size;
	if (flsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (flsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fold, buffer, flsize);
	buffer[flsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fold);
	for (in = 0; in < flsize; in++)
		if (buffer[in] == '\n')
		{
			buffer[in] = 0;
			build_history_list(info, buffer + lst, lcount++);
			lst = in + 1;
		}
	if (lst != in)
		build_history_list(info, buffer + lst, lcount++);
	free(buffer);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;
	add_node_end(&nd, buf, linecount);

	if (!info->history)
		info->history = nd;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int i = 0;

	while (nd)
	{
		nd->num = i++;
		nd = nd->next;
	}
	return (info->histcount = i);
}


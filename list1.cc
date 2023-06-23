#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @h: pointer the to first node
 * Return: size of list
 */


size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of strings of the list to strings.
 * @head: pointer to the first node
 * Return: array of strings
 */


char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	char *str;
	char **strs;
	size_t a = list_len(head);
	size_t j;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; nd; nd = nd->next, a++)
	{
		str = malloc(_strlen(nd->str) + 1);
		if (!str)
		{
			for (j = 0; j < a; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nd->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}

/**
 * print_list - prints all the elements of a list_t in the list
 * @h: pointer to first node
 * Return: size of list
 */


size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns a node in which the  string starts with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pi = NULL;

	while (node)
	{
		pi = starts_with(node->str, prefix);
		if (pi && ((c == -1) || (*pi == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the number index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}

#include "shell.h"

/**
 * add_node - adds a node to the beginning of the list
 * @head: address of the pointer to head node
 * @str: string of field of node
 * @num: numbernode index used by history
 * Return: size(number) of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nw_hd;

	if (!head)
		return (NULL);
	nw_hd = malloc(sizeof(list_t));
	if (!nw_hd)
		return (NULL);
	_memset((void *)nw_hd, 0, sizeof(list_t));
	nw_hd->num = num;
	if (str)
	{
		nw_hd->str = _strdup(str);
		if (!nw_hd->str)
		{
			free(nw_hd);
			return (NULL);
		}
	}
	nw_hd->next = *head;
	*head = nw_hd;
	return (nw_hd);
}

/**
 * add_node_end - adds a node to the tailend of the linked list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list(number)
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nd;
	list_t *nd;

	if (!head)
		return (NULL);

	nd = *head;
	new_nd = malloc(sizeof(list_t));

	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = _strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*head = new_nd;
	return (new_nd);
}
/**
 * print_list_str - prints only the string element of a list_t list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes a node of a given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node;
	list_t *pnode;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			pnode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		pnode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all the elements of a  node in a list.
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nnode;
	list_t *node;
	list_t *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nnode = node->next;
		free(node->str);
		free(node);
		node = nnode;
	}
	*head_ptr = NULL;
}

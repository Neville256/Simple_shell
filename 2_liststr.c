#include "main.h"

/**
 * list_len - linked list length determines
 * @h: first node pointer
 *
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - list->str array of strings
 * @head: firs node pointer
 *
 * Return: string of arrays
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t k = list_len(head), g;
	char **strs;
	char *str;

	if (!head || !k)
	return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
	return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
	{
		for (g = 0; g < k; g++)
		free(strs[g]);
		free(strs);
		return (NULL);

	}

	str = strcpy(str, node->str);
	strs[k] = str;
}
strs[k] = NULL;
return (strs);
}

/**
 * print_list - all elements prints list_t linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
{
	_eputs(convert_number(h->num, 10, 0));
	_putchar(':');
	_putchar(' ');
	_eputs(h->str ? h->str : "(nil)");
	_eputs("\n");
	h = h->next;
	k++;
}
return (k);
}

/**
 * node_starts_with - string starts with prefix node return
 * @node: list head pointer
 * @prefix: match string
 * @c: prefix match next char
 *
 * Return: node matches or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - node gets index
 * @head: list head pointer
 * @node: node pointer
 *
 * Return: node index or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}

#include "main.h"
/**
 * add_node - node added at the start of a list
 * @head: head node addressed by pointer
 * @str: node field
 * @num: histroy used index node
 *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *brandnew_head;

	if (!head)
	return (NULL);

	brandnew_head = malloc(sizeof(list_t));
	if (!brandnew_head)
		return (NULL);
	_memset((void *)brandnew_head, 0, sizeof(list_t));
	brandnew_head->num = num;
	if (str)
	{
		brandnew_head->str = _strdup(str);
		if (!brandnew_head->str)
		{
			free(brandnew_head);
			return (NULL);
		}
	}
	brandnew_head->next = *head;
	*head = brandnew_head;
	return (brandnew_head);
}

/**
 * add_node_end - node added to the end of list
 * @head: head node address to pointer
 * @str: node field str
 * @num: history used by index node
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *brandnew_node, *node;

	if (!head)
	return (NULL);

	node = *head;
	brandnew_node = malloc(sizeof(list_t));
	if (!brandnew_node)
	return (NULL);
	_memset((void *)brandnew_node, 0, sizeof(list_t));
	brandnew_node->num = num;
	if (str)
	{
		brandnew_node->str = _strdup(str);
		if (!brandnew_node->str)
		{
		free(brandnew_node);
		return (NULL);
	}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = brandnew_node;
	}
	else
		*head = brandnew_node;
	return (brandnew_node);
	}
/**
 * print_list_str - list_t linked list prints only str
 * @h: first node of pointer
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_eputs(h->str ? h->str : "(nil)");
		_eputs("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - given index delete node
 * @head: first node to address pointer
 * @index: delete index
 *
 * Return: 1 success and 0 fail
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *past_node;
	unsigned int k = 0;

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
		if (k == index)
		{
			past_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		past_node = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - list of all nodes free
 * @head_ptr: head node to address pointer
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

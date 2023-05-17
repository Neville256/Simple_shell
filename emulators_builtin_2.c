#include "main.h"

/**
 * _myhistory - displays history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Maintains
 * constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *o, d;
	int ret;

	o = _strchr(str, '=');
	if (!o)
		return (1);
	d = *o;
	*o = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*o = d;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *o;

	o = _strchr(str, '=');
	if (!o)
		return (1);
	if (!*++o)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *o = NULL;

	if (node)
	{
		o = _strchr(node->str, '=');
		_putchar('\'' + 1);
		_puts(o + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Maintains
 * constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *o = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		o = _strchr(info->argv[k], '=');
		if (o)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}

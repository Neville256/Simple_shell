#include "main.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Maintains
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Maintains
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t k = 0;
	char *o;

	if (!node || !var)
		return (0);

	while (node)
	{
		o = starts_with(node->str, var);
		if (o && *o == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), k);
			k = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Maintains
 *        constant function prototype.
 * @var: string env var property
 * @value: string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffs = NULL;
	list_t *node;
	char *o;

	if (!var || !value)
		return (0);

	buffs = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffs)
		return (1);
	strcpy(buffs, var);
	_strcat(buffs, "=");
	_strcat(buffs, value);
	node = info->env;
	while (node)
	{
		o = starts_with(node->str, var);
		if (o && *o == '=')
		{
			free(node->str);
			node->str = buffs;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffs, 0);
	free(buffs);
	info->env_changed = 1;
	return (0);
}

#include "main.h"

/**
 * chain - test if current char buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @o: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *o)
{
	size_t l = *o;

	if (buf[l] == '|' && buf[l + 1] == '|')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_types = CMD_OR;
	}
	else if (buf[l] == '&' && buf[l + 1] == '&')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_types = CMD_AND;
	}
	else if (buf[l] == ';')
	{
		buf[l] = 0;
		info->cmd_buf_types = CMD_CHAIN;
	}
	else
		return (0);
	*o = l;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @o: address of current position in buf
 * @k: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *o, size_t k, size_t len)
{
	size_t l = *o;

	if (info->cmd_buf_types == CMD_AND)
	{
		if (info->status)
		{
			buf[k] = 0;
			l = len;
		}
	}
	if (info->cmd_buf_types == CMD_OR)
	{
		if (!info->status)
		{
			buf[k] = 0;
			l = len;
		}
	}

	*o = l;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int k;
	list_t *node;
	char *o;

	for (k = 0; info->argv[k]; k++)
	{
		node = node_starts_with(info->alias, info->argv[k], '=');
		if (!node)
			return (0);
		free(info->argv[k]);
		o = strchr(node->str, '=');
		if (!o)
			return (0);
		o = _strdup(o + 1);
		if (!o)
			return (0);
		info->argv[k] = o;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int k;
	list_t *node;

	for (k = 0; info->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;

		node = node_starts_with(info->env, &(info->argv[k][1]), '=');
		if (node)
		{
			char *value = strchr(node->str, '=') + 1;

			restore_string(&(info->argv[k]), _strdup(value));
		}
		else if (!_strcmp(info->argv[k], "$?"))
		{
			char *status_str = convert_number(info->status, 10, 0);

			restore_string(&(info->argv[k]), _strdup(status_str));
			free(status_str);
		}
		else if (!_strcmp(info->argv[k], "$$"))
		{
			char *pid_str = convert_number(getpid(), 10, 0);

			restore_string(&(info->argv[k]), _strdup(pid_str));
			free(pid_str);
		}
		else
		{
			restore_string(&(info->argv[k]), _strdup(""));
		}
	}
	return (1);
}

/**
 * restore_string - replaces a string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int restore_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

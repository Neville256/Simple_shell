#include "main.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buffs, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffs = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffs)
		return (NULL);
	buffs[0] = 0;
	strcpy(buffs, dir);
	_strcat(buffs, "/");
	_strcat(buffs, HIST_FILE);
	return (buffs);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fwd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fwd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fwd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_eputs(node->str, fwd);
		putw('\n', fwd);
	}
	putw(BUF_FLUSH, fwd);
	close(fwd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int k, last = 0, linecount = 0;
	ssize_t fwd, rdlen, fsize = 0;
	struct stat st;
	char *buffs = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fwd = open(filename, O_RDONLY);
	free(filename);
	if (fwd == -1)
		return (0);
	if (!fstat(fwd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffs = malloc(sizeof(char) * (fsize + 1));
	if (!buffs)
		return (0);
	rdlen = read(fwd, buffs, fsize);
	buffs[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffs), 0);
	close(fwd);
	for (k = 0; k < fsize; k++)
		if (buffs[k] == '\n')
		{
			buffs[k] = 0;
			build_history_list(info, buffs + last, linecount++);
			last = k + 1;
		}
	if (last != k)
		build_history_list(info, buffs + last, linecount++);
	free(buffs);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: history linecount, history count
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list after changes
 * @info: Structure containing potential arguments.
 *
 * Return: new history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (info->histcount = k);
}

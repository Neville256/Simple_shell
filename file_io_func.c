#include "main.h"

/**
 * get_history_file - collect history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - file creates or modify existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
<<<<<<< HEAD
    ssize_t fwd;
    char *filename = get_history_file(info);
    list_t *node = NULL;
    int flush_value;
=======
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a

    if (!filename)
        return (-1);

<<<<<<< HEAD
    flush_value = BUF_FLUSH;

    fwd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(filename);
    if (fwd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        _eputs(node->str);
        write(fwd, "\n", 1);
    }

    write(fwd, &flush_value, 1);

    close(fwd);

    return (1);
=======
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (-1);
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a
}
/**
 * read_history - file reads history
 * @info: parameter struct
 *
 * Return: success histcount , if error 0 occurs
 */
int read_history(info_t *info)
{
	int k, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
<<<<<<< HEAD

	fwd = open(filename, O_RDONLY);
=======
	fd = open(filename, O_RDONLY);
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a
	free(filename);
	if (fd == -1)
		return (0);
<<<<<<< HEAD

	if (fstat(fwd, &st) == 0)
=======
	if (fstat(fd, &st) == 0)
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a
		fsize = st.st_size;

	if (fsize < 2)
		return (0);
<<<<<<< HEAD

	buffs = malloc(sizeof(char) * (fsize + 1));
	if (!buffs)
		return (0);

	rdlen = read(fwd, buffs, fsize);
	buffs[fsize] = '\0';

	if (rdlen <= 0)
		return (free(buffs), 0);

	close(fwd);

=======
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a
	for (k = 0; k < fsize; k++)
	{
		if (buf[k] == '\n')
		{
			buf[k] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = k + 1;
		}
	}

	if (last != k)
<<<<<<< HEAD
		build_history_list(info, buffs + last, linecount++);

	free(buffs);

=======
		build_history_list(info, buf + last, linecount++);
	free(buf);
>>>>>>> 3327c3da89e3ad9ca63adf77ad6fb05021529f4a
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);

	return (info->histcount);
}

/**
 * build_history_list -  history linked list added to history
 * @info: potential arguments that contain structure.
 * @buf: buffer
 * @linecount: history of line count
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
 * renumber_history - history renumber after changes
 * @info: potential arguments of structure contained.
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

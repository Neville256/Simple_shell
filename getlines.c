#include "main.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

	/*bfree((void **)info->cmd_buf);*/
	free(*buf);

	free(*buffs);
	*buf = NULL;
	signal(SIGINT, signthandler);
	#if USE_GETLINE
	r = getline(buffs, &len_p, stdin);
	#else
	r = _getline(info, buf, &len_p);
	#endif
	if (r > 0)
	{
		if ((*buf)[r - 1] == '\n')
		{

			(*buf)[r - 1] = '\0'; /* remove trailing newline */
			r--;
			}
			info->lineamount_flag = 1;
			comments_remove(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */

			(*buffs)[r - 1] = '\0';
			r--;
			}
			info->lineamount_flag = 1;
			comments_remove(*buffs);
			build_history_list(info, *buffs, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets line minus the newline
 * @info: parameter struct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{

	char *o = *(info->buf_p);
	char *buffs = NULL; /* the ';' command chain buffer */

	size_t k = 0, l = 0 , len = 0;
	ssize_t r = 0;
	char **buf_p = &(info->arg),
	char *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buffs, &len);
	if (r == -1)
		return (-1);
	if (len > 0)
	{
		l = k;
		p = buffs + k;

		check_chain(info, buffs, &l, k, len);
		while (l < len)
		{
			if (is_chain(info, buf_p, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_types = CMD_NORM;
		}

		*buf_p = o;
		return (_strlen(o));
	}

	*(buf_p) = info->buf;
	return (r);
}}
/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buffs: buffer
 * @k: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return (0);
	r = read(info->scanfd, buf, SCAN_BUF_SIZE);
	if (r >= 0)
		*k = r;
	return (r);
}

/**
 * _getline - gets next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffs[SCAN_BUF_SIZE];
	static size_t k, len;
	size_t l;
	ssize_t r = 0, t = 0;
	char *o = NULL, *new_p = NULL, *d;

	o = *ptr;
	if (o && length)
		t = *length;
	if (k == len)
		k = len = 0;

	r = read_buf(info, buffs, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	d = strchr(buffs + k, '\n');
	l = d ? 1 + (unsigned int)(d - buffs) : len;
	new_p = _realloc(o, t, t ? t + l : l + 1);
	if (!new_p)
		return (o ? free(o), -1 : -1);

	if (t)
		_strcat(new_p, buffs + k, l - k);
	else
		strncpy(new_p, buffs + k, l - k + 1);

	t += l - k;
	k = l;
	o = new_p;

	if (length)
		*length = t;
	*ptr = o;
	return (t);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_eputs("\n");
	_eputs("$ ");
	_putchar(BUF_FLUSH);
}

#include "main.h"

/**
 * input_buf - chained commands buffers
 * @info: struct parameter
 * @buf: buffer address
 * @len: len var address
 *
 * Return: read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_b = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginthandler);

		q = getline(buf, &len_b, stdin);
		q = _getline(info, buf, &len_b);

		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf[q - 1] = '\0');
				 q--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = q;
				info->cmd_buf = buf;
			}
		}
	}
	return (q);
}
/**
 * get_input - subtract newline get line
 * @info: struct param
 *
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t k, l, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1)
		return (-1);
	if (len)
	{
		l = k;
		p = buf + k;

		check_chain(info, buf, &l, len);
		while (l < len)
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}
		k = l + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (q);
}

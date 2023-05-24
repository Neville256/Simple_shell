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

	if (!*len)/* fill buffer if nothing left*/
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginthandler);
#if USE_GETLINE
		q = getline(buf, &len_b, stdin);
#else
		q = _getline(info, buf, &len_b);
#endif
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf[q - 1] = '\0');/*trailing new line remove*/
				 q--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) command chain */
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
	static char *buf;/* buffer chain is the ;*/
	static size_t k, l, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1)/* EOF */
		return (-1);
	if (len) /* chain buffer left in commands */
	{
		l = k; /* current buf position to new int iterator*/
		p = buf + k; /* return get pointer */

		check_chain(info, buf, &l, len, 1024);
		while (l < len) /* end semicolon to iteration */
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

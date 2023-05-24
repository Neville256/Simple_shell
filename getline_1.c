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
		l = k;
		p = buf + k;

		check_chain(info, buf, &l, len, 1024);
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

/**
* siginthandler - a fuction that invoked for a signal
* function and show the prompt
* @sig_n: number of the signal
*/
void siginthandler(int sig_n)
{
	(void) sig_n;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

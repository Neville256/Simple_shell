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
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @k: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*k = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[1024];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
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

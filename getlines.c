#include "main.h"
#include <fcntl.h>
#include <errno.h>

ssize_t input_buf(info_t *info, char **buffs, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;
	char **buffs = buffs;

	if (!*len)
	{
		free(*buffs);
		*buffs = NULL;
		signal(SIGINT, siginthandler);
#if USE_GETLINE
		r = getline(buffs, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lineamount_flag = 1;
			comments_remove(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return r;
}

ssize_t get_input(info_t *info)
{
	static char buffs[SCAN_BUF_SIZE];
	static size_t k, l, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buffs, &len);
	if (r == -1)
		return -1;
	if (len)
	{
		l = k;
		p = buffs + k;

		check_chain(info, buffs, &l, k, len);
		while (l < len)
		{
			if (is_chain(info, *buf_p, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_types = CMD_NORM;
		}

		*buf_p = p;
		return strlen(p);
	}

	*buf_p = buffs;
	return r;
}

ssize_t read_buf(info_t *info, char *buf, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return 0;
	r = read(info->scanfd, buf, SCAN_BUF_SIZE);
	if (r >= 0)
		*k = r;
	return r;
}

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
		return -1;

	d = strchr(buffs + k, '\n');
	l = d ? 1 + (unsigned int)(d - buffs) : len;
	new_p = realloc(o, t ? t + l : l + 1);
	if (!new_p)
		return o ? (free(o), -1) : -1;

	if (t)
		strncat(new_p, buffs + k, l - k);
	else
		strncpy(new_p, buffs + k, l + 1);

	t += l - k;
	k = l;
	o = new_p;

	if (length)
		*length = t;
	*ptr = o;
	return t;
}

void siginthandler(int)
{
	_eputs("\n");
	_eputs("$ ");
	_putchar(BUF_FLUSH);
}

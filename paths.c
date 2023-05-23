#include "main.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return (0);

	if (S_ISREG(st.st_mode))
		return (1);

	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0, l = 0;

	for (k = start; k < stop; k++)
	{
		if (pathstr[k] != ':')
			buf[l++] = pathstr[k];
	}
	buf[l] = '\0';
	return (buf);
}

/**
 * find_path - finds this cmd in PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int k = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[k] || pathstr[k] == ':')
		{
			path = dup_chars(pathstr, curr_pos, k);
			if (*path == '\0')
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[k])
				break;
			curr_pos = k + 1;
		}
		k++;
	}
	return (NULL);
}


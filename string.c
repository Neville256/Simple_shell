#include "main.h"

/**
 * _strncmp - a function that compares two strings.
 * @str1: the first string to compare.
 * @str2: the second string to compare.
 * @n: number of bytes to compare.
 *
 * Return: 0 if two strings are the same and if not
 * returns the diffrence between the two different characters.
 */
int _strncmp(char *str1, char *str2, size_t n)
{
	size_t m;

	for (m = 0; m < n; m++)
	{
		if (str1[m] != str2[m])
			return (str1[m] - str2[m]);
		if (str1[m] == '\0')
			return (0);
	}
	return (0);
}

/**
 * _strlen - function that count the lenght of a string.
 * @str: string to be counted.
 *
 * Return: lenght.
 */
int _strlen(char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * _strdup - function that duplicates a string.
 * @str: string to duplicate.
 *
 * Return: the new string (duplicate)
 */
char *_strdup(const char *str)
{
	size_t k, len = strlen(str) + 1;
	char *new_str = malloc(len);

	if (new_str == NULL)
	{
		return (NULL);
	}

	for (k = 0; k < len; k++)
	{
		new_str[k] = str[k];
	}
	return (new_str);
}

/**
 * _strcmp - function that compares two strings.
 * @s1: the first string to compare.
 * @s2: the second string to compare.
 * Return: 0 if the two strings are the same and if not
 * it returns the diffrence between the first two different characters.
 */
int _strcmp(char *s1, char *s2)
{
	int l, k, result;

	l = 0;
	result = 0;
	while (s1[l] != '\0')
		l++;
	for (k = 0; k <= l; k++)
	{
		if (s1[k] != s2[k])
		{
			result = s1[k] - s2[k];
			break;
		}
	}
	return (result);
}

/**
 * _strcat - function that appends the src string to the dest string,
 * overwriting a terminating null byte (\0) at end of dest,
 * then adds a terminating null byte.
 * @path: pointer appended by command.
 * @command: pointer appended to path.
 * Return: pointer too resulting string dest.
 */
char *_strcat(char *path, char *command)
{
	int x;
	unsigned int k, l, path_len, command_len, sizebuff;
	char *p;

	(void) x;
	path_len = _strlen(path);
	command_len = _strlen(command);
	sizebuff = path_len + command_len + 2;
	p = malloc(sizeof(char) * sizebuff);
	if (!p)
	{
		x = write(STDERR_FILENO, "Error: malloc failed\n", 22);
		exit(98);
	}
	for (k = 0; k < path_len; k++)
		p[k] = path[k];
	p[k] = '/';
	for (k++, l = 0; l < command_len; l++)
		p[k + l] = command[l];
	p[k + l] = '\0';
	return (p);
}

#include "main.h"


/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int k, l, m, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[k], d))
			k++;
		m = 0;
		while (!is_delim(str[k + m], d) && str[k + m])
			m++;
		s[l] = malloc((m + 1) * sizeof(char));
		if (!s[l])
		{
			for (m = 0; m < l; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < m; n++)
			s[l][n] = str[k++];
		s[l][n] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * strtow2 - splits a string into words using a delimiter
 * @str: the input string
 * @d: the delimiter character
 * Return: array of strings or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int k, m, l, h, countwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (k = 0; str[k] != '\0'; k++)
	{
		if ((str[k] != d && str[k + 1] == d) ||
				(str[k] != d && !str[k + 1]) || str[k + 1] == d)
			countwords++;
	}

	if (countwords == 0)
		return (NULL);
	s = malloc((countwords + 1) * sizeof(char *));
	if (!s)
		return (NULL);

	for (k = 0, m = 0; m < countwords; m++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		l = 0;
		while (str[k + l] != d && str[k + l] && str[k + l] != d)
			l++;
		s[m] = malloc((l + 1) * sizeof(char));
		if (!s[m])
		{
			for (l = 0; l < m; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (h = 0; h < l; h++)
			s[m][h] = str[k++];
		s[m][h] = '\0';
	}
	s[m] = NULL;
	return (s);
}

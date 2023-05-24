#include "main.h"
/**
 * strtow - words splint into string
 * @str: string inputs
 * @d: string delimeter
 * Return: string of arrays or NULL on fail
 */
char **strtow(char *str, char *d)
{
	int k, m, l, h, countwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
	d = " ";
	for (k = 0; str[k] != '\0'; k++)
	if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) ||
	!str[k + 1]))
	countwords++;
	if (countwords == 0)
	return (NULL);
	s = malloc((1 + countwords) * sizeof(char *));
	if (!s)
	return (NULL);
	for (k = 0, m = 0; m < countwords; m++)
	{
		while (is_delim(str[k], d))
			k++;

		k = 0;
		while (!is_delim(str[k + l], d) && str[k + l])
			k++;
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
		s[m][h] = 0;
		}
		s[m] = NULL;
		return (s);
}

/**
 * strtow2 - string into words splits
 * @str: string input
 * @d: delimeter
 * Return: array of string or null fail
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
	s = malloc((1 + countwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (k = 0; (m = 0); m < countwords; m++)
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
			{
				free(s[l]);
			}
				free(s);
				return (NULL);
			}
			for (h = 0; h < l; h++)
			s[m][h] = str[k++];
			s[m][h] = 0;
		}
		s[m] = NULL;
		return (s);
}

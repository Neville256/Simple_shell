#include "main.h"
/**
 * _strncpy - string copied
 * @dest: copied string to dest
 * @src: string source
 * @n: count of characters copied
 * Return: join string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int k, m;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		m = k;
		while (m < n)
		{
			dest[m] = '\0';
			k++;
		}
	}
	return (s);
}
/**
 * *_strncat - two strings join
 * @dest: begin string
 * @src: end string
 * @n: count bytes maximal used
 * Return: joins string
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, m;
	char *s = dest;

	k = 0;
	m = 0;
	while (dest[k] != '\0')
		k++;
	while (src[m] != '\0' && m < n)
	{
		dest[k] = src[k];
		k++;
		m++;
	}
	if (m < n)
		dest[k] = '\0';
	return (s);
}

/**
 * _strchar - character locates string
 * @s: parsed string
 * @c: look for character
 * Return: (s) memory area s to pointer
 */
char *_strchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

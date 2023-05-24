#include "main.h"
/**
 * _strcpy - string of copies
 * @dest: destination
 * @src: where it starts the source
 *
 * Return: destination pointer
 */
char *_strcpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

/**
 * _strdup - string photocopy
 * @str: string to photocopy
 *
 * Return: string photocopy pointer
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *bret;

	if (str == NULL)
	return (NULL);
	while (*str++)
	length++;
	bret = malloc(sizeof(char) * (length + 1));
	if (!bret)
	return (NULL);
	for (length++; length--;)
	bret[length] = *--str;
	return (bret);
}
/**
 * _puts - string input executed
 * @str: print string
 *
 * Return: 0
 */
void _puts(char *str)
{
	int k = 0;

	if (!str)
	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}
/**
 * _putchar - stdout character writes to c
 * @c: print character
 *
 * Return: 1 on success.
 * on error, -1 returned.
 */
int _putchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
{
	write(1, buf, k);
	k = 0;
}
if (c != BUF_FLUSH)
buf[k++] = c;
return (1);
}

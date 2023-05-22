#include "main.h"

/**
 *_eputs - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}

/**
 * _eputchar - writes character d to stderr
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, errno is set appropriately.
 */
int _eputchar(char d)
{
	static int k;
	static char buffs[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buffs, k);
		k = 0;
	}
	if (d != BUF_FLUSH)
		buffs[k++] = d;
	return (1);
}

/**
 * _putfwd - writes the character d to given fwd
 * @d: character to print
 * @fwd: filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, errno is set appropriately.
 */
int _putfwd(char d, int fwd)
{
	static int k;
	static char buffs[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fwd, buffs, k);
		k = 0;
	}
	if (d != BUF_FLUSH)
		buffs[k++] = d;
	return (1);
}

/**
 *_putsfwd - prints an input string
 * @str: the string to be printed
 * @fwd: the filedescriptor to write to
 *
 * Return: number of chars put
 */
int _putsfwd(char *str, int fwd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfwd(*str++, fwd);
	}
	return (i);
}

#include "main.h"
/**
 * _erratoi - string to integer converted
 * @s: convert string
 * Return: 0 no number string, -1 otherwise
 */
int _erratoi(char *s)
{
	int k = 0;
	unsigned long int result = 0;

	if (*s == '+')
	s++;

	for (k = 0; s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			result *= 10;
		result += (s[k] - '0');
		if (result > INT_MAX)
			return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * print_error - error message to print
 * @info: return info struct parameter
 * @estr: error type contain string
 * Return: 0 number string , else -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - number(base 10) function prints decimal integer
 * @input: input result
 * @fd: file to write to
 *
 * Return: characters print number
 */
int print_d(int input, int fd)
{
		int (*__putchar)(char) = _putchar;
		int k, amount = 0;
		unsigned int _abs_, recent;

		if (fd == STDERR_FILENO)
		__putchar = _eputchar;
		if (input < 0)
		{
		_abs_ = -input;
		__putchar('-');
		amount++;
		}
		else
		{
			_abs_ = input;
			recent = _abs_;
		}
		for (k = 1000000000; k > 1; k /= 10)
		{
			if (_abs_ / k)
			{
				__putchar('0' + recent / k);
				amount++;
			}
			recent %= k;
		}
		__putchar('0' + recent);
		amount++;

		return (amount);
}
/**
 * convert_number - clone itoa converter function
 * @num: number
 * @base: the base input
 * @flags: flags argumented
 *
 * Return: a string is returned
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long d = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		d = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[d % base];
		d /= base;
	} while (d != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - replace function of '#' with '0'
 * @buf: string modifed to address
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
	if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
	{
		buf[k] = '\0';
		break;
	}
}

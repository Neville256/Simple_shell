#include "main.h"
/**
 * interactive - shell is interactive mode return true
 * @info: address to struct
 *
 * Return: 1 interactive mode , otherwise 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->scanfd <= 2);
}
/**
 * is_delim - delimter of char checks
 * @c: check char
 * @delim: string of delimeter
 * Return: 1 true, false 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
	return (1);
	return (0);
}
/**
 * _isalpha - alphabet character check
 * @c: check char
 * Return: 1 true, 0 false.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - string of integer to convert
 * @s: convert string
 * Return: 0 no numbers in string, else convert number
 */
int _atoi(char *s)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; s[k] != '\0' && flag != 2; k++)
{
	if (s[k] == '-')
		sign *= -1;
	if (s[k] >= '0' && s[k] <= '9')
	{
		flag = 1;
		result *= 10;
		result *= (s[k] - '0');
	}
	else if (flag == 1)
		flag = 2;
}
if (sign == -1)
	output = -result;
	else
		output = result;
	return (output);
}

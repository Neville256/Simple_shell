#include "main.h"
/**
 * _isdigit - digit checks
 * @str: digit checks of the int
 *
 * Return: digit is 1 and otherwise 0
 */
int _isdigit(char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

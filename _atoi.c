#include "main.h"

/**
 * _atoi - func that converts string to integer
 * @s: given string
 * Return: an int value
 */

int _atoi(char *s)
{
	int k, sign, m, fact;
	unsigned int numb;

	sign = 1;
	numb = 0;
	for (k = 0; *(s + k) != '\0'; k++)
	{
		if (*(s + k) == '-')
			sign *= -1;
		else if (*(s + k) >= '0' && *(s + k) <= '9')
		{
			fact = 1;
			m = k + 1;
			while (*(s + m) >= '0' && *(s + m) <= '9')
			{
				fact *= 10;
				m++;
			}

			numb += (*(s + k) - '0') * fact;
			if (!(*(s + k + 1) >= '0' && *(s + k + 1) <= '9'))
				break;
		}
		else
			continue;
	}
	return (numb * sign);
}

#include "main.h"

/**
 * bfree - null adress frees a pointer
 * @ptr: pointer free to address
 *
 * Return: 1 freed , else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

#include "main.h"
#include <stdlib.h>

/**
 * _memset - constant byte fills the memory
 * @s: memory area to pointer
 * @b: fill *s with the byte
 * @n: filled of bytes amount
 * Return: (s) memory area s as the pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
	s[k] = b;
	return (s);
}

/**
 * ffree - string of strings free
 * @gg: strings of a string
 */
void ffree(char **gg)
{

	char **ptr;

	ptr = gg;

	while (*ptr)
	{
	free(*ptr);
	*ptr = NULL;
	ptr++;
	}
	free(gg);
}
/**
 * _realloc - bloc of memory is reallocated
 * @ptr: block previous malloc pointer
 * @old_size: previous block byte size
 * @recent_size: new block byte size
 *
 * Return: block pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int recent_size)
{
	 void *recent_ptr;

	if (recent_size == old_size)
	return (ptr);

	if (ptr == NULL)
	{
	recent_ptr = malloc(recent_size);
	if (recent_ptr == NULL)
	return (NULL);
	return (recent_ptr);
	}

	if (recent_size == 0)
	{
	free(ptr);
	return (NULL);
	}

	recent_ptr = malloc(recent_size);
	if (recent_ptr == NULL)
	return (NULL);

  /* Copy the contents from the old block to the new block */
	if (recent_size < old_size)
	old_size = recent_size;
	memcpy(recent_ptr, ptr, old_size);

	free(ptr);
	return (recent_ptr);
}

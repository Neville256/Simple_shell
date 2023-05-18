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
 * my_free - string of strings free
 * @gg: strings of a string
 */
void my_free(char **gg)
{
	if (!gg || !*gg)
	return;
	char **ptr = gg;

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
	char *p;

	if (!ptr)
	return (malloc(recent_size));
	if (!recent_size)
		return (free(ptr), NULL);
	if (recent_size == old_size)
	return (ptr);

	p = malloc(recent_size);
	if (!p)
	return (NULL);

	unsigned int size  = old_size < recent_size ? old_size : recent_size;

	while (old_size--)
	p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

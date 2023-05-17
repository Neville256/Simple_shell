#include "main.h"
/**
 * _strlen - string length is returned
 * @s: check length of string to check
 *
 * Return: string length of an int
 */
int _strlen(char *s)
{
	int k = 0;

	if (!s)
	return (0);

	while (*s++)
	k++;
	return (k);
}

/**
 * _strcmp - two strings compares performance
 * @s1: begin string
 * @s2: end string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - check if pin starts with heavyduty
 * @heavyduty: search for heavyduty
 * @pin: find substring
 *
 * Return: heavyduty address of next or NULL
 */
char *starts_with(const char *heavyduty, const char *pin)
{
	while (*pin)
	if (*pin++ != *heavyduty++)
	return (NULL);
	return ((char *)heavyduty);
}
/**
 * _strcat - two strings joined together
 * @dest: dest of buffer
 * @src: originator of buffer
 *
 * Return: dest buffer pointer
 */
char *_strcat(char *dest, char *src)
{
char *bret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (bret);
}

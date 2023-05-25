#include "main.h"

/**
 * _getenv - Get value of an env variable.
 * @variable_name: Pointer to null-terminated string representing
 * the name of the environment variable.
 *
 * Return: NULL pointer.
 */
char *_getenv(char *variable_name)
{
	int k;
	size_t name_length = _strlen(variable_name);

	for (k = 0; environ[k] != NULL; k++)
	{
		if (_strncmp(environ[k], variable_name, name_length) == 0
			&& environ[k][name_length] == '=')
		{
			return (environ[k] + name_length + 1);
		}
	}

	return (NULL);
}

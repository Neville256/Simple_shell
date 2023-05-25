#include "main.h"
/**
 * env_args - variables print environment
 * @args: strings containing arguments to a double pointer array
 *
 * Return: void.
 */
void env_args(char **args)
{
	char **env, *str;
	ssize_t x;

	(void) x;
	if (args[1] != NULL)
	{
		str = "env: '";
		x = write(STDERR_FILENO, str, _strlen(str);
		x = write(STDERR_FILENO, args[1], _strlen(args[1]));
		str = "': no such file directory\n";
		x = write(STDERR_FILENO, str, _strlen(str));
	}
	else
	{
	env = environ;
	while (*env)
	{
		x = write(1, *env, _strlen(*env));
		x = write(1, "\n", 2);
		env++;
	}
	}
}

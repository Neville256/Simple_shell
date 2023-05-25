#include "main.h"
/**
 * command_split - splits command line of function
 * @str: command line to pointer
 *
 * Return: strings of array
 */
char **command_split(char *str)
{
	char *token, *token_hash, **args;
	int k, x, number_comands;

	(void) x;
	number_comands = 0;
	if (str[0] != ' ' && str[0] != '\t' && str[0] != '\n')
		number_comands++;
	for (k = 0; str[k] != '\0'; k++)
	{
		if ((str[k] == ' ' || str[k] == '\t') && str[k + 1] != ' '
				&& str[k + 1] != '\t' && str[k + 1] != '\n')
			number_comands++;

	}
	if (number_comands == 0)
		return (NULL);
	args = malloc((number_comands + 1) * sizeof(char *));
	if (args == NULL)
	{
		x = write(STDERR_FILENO, "Error: malloc failed\n", 22);
		free(str);
		exit(98);
	}
	token_hash = strtok(str, "#");
	token = strtok(token_hash, DELIM);
	k = 0;
	while (token)
	{
		args[k] = _strdup(token);
		if (args[k] == NULL)
		{
			x = write(STDERR_FILENO, "Error: malloc failed\n", 22);
			free_args(args);
			exit(98);
		}
		token = strtok(NULL, DELIM);
		k++;
	}
	args[number_comands] = NULL;
	return (args);
}

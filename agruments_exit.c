#include "main.h"

void free_args(char **args);
/**
 * exit_arguments - checks for exit errors of a function
 * @argv: vector arguments
 * @args: arguments output
 * @s: pointer to command
 * @x: counter iterations
 * @exit_fail: status checker failure exit
 * @exit_status: status exit
 * Return: void.
 */
void exit_arguments(char **argv, char **args, char *s, int x, int *exit_fail,
int *exit_status){
	unsigned int num;

	if (!args[1])
	{
		if (*exit_fail == 2 || *exit_status == 2)
		{
			free_args(args);
			free(s);
			exit(2);
		}
		if (*exit_status == 127)
		{
			free_args(args);
			free(s);
			exit(127);
		}
		else
		{
			free_args(args);
			free(s);
			exit(0);
		}
	}
	if (_isdigit(args[1]) == 1)
	{
		num = (unsigned int) _atoi(args[1]);
		if (num > (unsigned int) INT_MAX)
		{
			exit_error(argv[0], args, x);
			*exit_fail = 2;
		}
		else
		{
			num %= 256;
			free_args(args);
			exit(num);
		}
	}
	else
	{
		exit_error(argv[0], args, x);
		*exit_fail = 2;
	}
	free_args(args);
}

/**
 * free_args - array of strings frees memory allocated
 * @args: array of strings to double pointer
 *
 * Return: void.
 */
void free_args(char **args)
{
	char **arg_ptr = args;

	while (*arg_ptr)
	{
		free(*arg_ptr);
		arg_ptr++;
	}
	free(args);
}

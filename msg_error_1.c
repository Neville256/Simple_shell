#include "main.h"
/**
 * command_error - command errors are checked in function
 * @argv: vectors argument
 * @cmd: command given
 * @count: main function counter
 * check_path: command checks if path or not
 * @exit_status: chile process exit status
 *
 * Return: void.
 */
void command_error(char *argv, char *cmd, int count, int check_path,
		int *exit_status)
{
	int x;
	char *num, *token;

	num = int_to_str(count);
	(void) x;
	if (check_path == 1)
	{
		token = strtok(cmd, "/");
		while (token)
		{
			cmd = token;
			token = strtok(NULL, "/");
		}
	}
	x = write(STDERR_FILENO, argv, _strlen(argv));
	x = write(STDERR_FILENO, ": ", 2);
	x = write(STDERR_FILENO, num, _strlen(num));
	x = write(STDERR_FILENO, ": ", 2);
	x = write(STDERR_FILENO, cmd, _strlen(cmd));
	x = write(STDERR_FILENO, ": ", 2);
	if (_strcmp(strerror(errno), "Permission denied") == 0)
	{
		perror("");
		*exit_status = 126;
	}
	else
	{
		x = write(STDERR_FILENO, "not found\n", 10);
		*exit_status = 127;
	}
	free(num);
}
/**
 * exit_error - checks for exit errors of functions
 * @argv: vector arguments to check
 * @args: command line interface
 * @count: main function of the counter
 *
 * Return: void.
 */
void exit_error(char *argv, char **args, int count)
{
	int x;
	char *num;

	num = int_to_str(count);
	(void) x;
	x = write(STDERR_FILENO, argv, _strlen(argv));
	x = write(STDERR_FILENO, ": ", 2);
	x = write(STDERR_FILENO, num, _strlen(num));
	x = write(STDERR_FILENO, ": ", 2);
	x = write(STDERR_FILENO, args[0], _strlen(args[0]));
	x = write(STDERR_FILENO, ": ILLEGAL number: ", 18);
	x = write(STDERR_FILENO, args[1], _strlen(args[1]));
	x = write(STDERR_FILENO, "\n", 2);
	free(num);
}

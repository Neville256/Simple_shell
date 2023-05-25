#include "main.h"

int check_path(char *str);
void int_handler(int sig_n);

/**
 * main - Performs a specific operation using argc and argv.
 * @argc: The argument count.
 * @argv: An array of strings containing the arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv)
{
	int check_p, status, exit_status;
	char *filepath, **args;
	pid_t pid;
	char *command = NULL, *p, *token, **env;
	size_t len = 0;
	ssize_t r, y = 0;
	int t, is_interactive, exit_failure = 0;


	exit_status = 0;
	(void) y;
	(void) argc;
	env = environ;
	is_interactive = isatty(STDIN_FILENO);
	filepath = NULL;

	t = 0;
	while (1)
	{
		t++;
		if (is_interactive)
		{
			y = write(1, "#cisfun$ ", 9);
		}
		signal(SIGINT, int_handler);
		r = getline(&command, &len, stdin);
		if (r == -1 && is_interactive)
		{
			write(1, "\n", 1);
			free(command);
			exit(exit_status);
		}
		if (r == -1 && !is_interactive)
		{
			free(command);
			exit(exit_status);
		}
		if (_strcmp(command, "\n") == 0 && is_interactive)
		{
			continue;
		}

		args = command_split(command);
		if (!args)
		{
			continue;
		}
		if (_strcmp(args[0], "exit") == 0)
		{
			exit_arguments(argv, args, command, t, &exit_failure,
					&exit_status);
			continue;
		}
		if (_strcmp(args[0], "env") == 0)
		{
			env_args(args);
			free_args(args);
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			free_args(args);
			y = write(STDERR_FILENO, "fork failed\n", 12);
			return (1);
		}
		else if (pid == 0)
		{
			check_p = check_path(args[0]);
			if (check_p != 0)
			{
				p = _getenv("PATH");
				token = strtok(p, ":");
				while (token != NULL)
				{
					filepath  = _strcat(token, args[0]);

					if (access(filepath, F_OK) != -1)
						break;
					token = strtok(NULL, ":");
					if (token != NULL)
					{
						free(filepath);
					}
				}
			}
			else
				filepath = args[0];
			execve(filepath, args, env);
			command_error(argv[0], args[0], t, check_p, &exit_status);
			if (check_p != 0)
				free(filepath);
			free_args(args);
			free(command);
			exit(exit_status);
		}
		else
		{
			wait(&status);
			free_args(args);
			exit_status = WEXITSTATUS(status);
		}
		fflush(stdin);
	}
	free(command);
	return (0);
}

/**
 * check_path - function that checks wheter a string is a path or not.
 * @str: given string.
 *
 * Return: 0 in success and 1 if failed.
 */
int check_path(char *str)
{
	int k;

	for (k = 0; str[k] != '\0'; k++)
		if (str[k] == '/')
			return (0);
	return (1);
}

/**
* int_handler - a fuction that invoked for a signal
* function and show the prompt
* @sig_n: number of the signal
*/
void int_handler(int sig_n)
{
	(void) sig_n;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

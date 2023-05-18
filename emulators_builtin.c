#include "main.h"

/**
 * _myexit - exits shell
 * @info: Structure containing potential arguments. maintain
 * constant function prototype.
 * Return: exits with a given status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int checkexit;

	if (info->argv[1])  /* If there is an exit argument */
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = checkexit;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes current directory of the process
 * @info: Structure containing potential arguments. maintains
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *t, *dirc, buffer[1024];
	int chdirc_ret;

	t = getcwd(buffer, 1024);
	if (!t)
		_eputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirc = _getenv(info, "HOME=");
		if (!dirc)
			chdirc_ret = chdir((dirc = _getenv(info, "PWD=")) ? dirc : "/");
		else
			chdirc_ret = chdir(dirc);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts("OLDPWD not set");
			_putchar('\n');
			return (1);
		}
		_eputs(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdirc_ret = chdir((dirc = _getenv(info, "OLDPWD=")) ? dirc : "/");
	}
	else
		chdirc_ret = chdir(info->argv[1]);
	if (chdirc_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes current directory of the process
 * @info: Structure containing potential arguments. maintains
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (arg_array[0])
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

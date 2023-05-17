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

	if (info->argv[1])  /* If there is an exit arguement */
	{
		checkexit = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirc = _getenv(info, "HOME=");
		if (!dirc)
			chdirc_ret =
				chdirc((dirc = _getenv(info, "PWD=")) ? dirc : "/");
		else
			chdirc_ret = chdirc(dirc);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirc_ret =
			chdirc((dirc = _getenv(info, "OLDPWD=")) ? dirc : "/");
	}
	else
		chdirc_ret = chdirc(info->argv[1]);
	if (chdirc_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
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
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

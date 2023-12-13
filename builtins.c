#include "shell.h"

/**
 * ela_exit - A function that exits the shell
 * @info: A structure that conatains arguments that will be
 * used functions and this format is applied to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int ela_exit(ela_info *info)
{
	int checker;

	if (info->argv[1])
	{
		checker = er_stoi(info->argv[1]);
		if (checker == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			e_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->err_num = er_stoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info:A structure that conatains arguments that will be
 * used functions and this format is applied to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int _mycd(ela_info *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("getcwd failure\n");
	if (!info->argv[1])
	{
		dir = ela_getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = ela_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!ela_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(ela_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = ela_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
		e_puts(info->argv[1]), error_putchar('\n');
	}
	else
	{
		ela__setenv(info, "OLDPWD", ela_getenv(info, "PWD="));
		ela__setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ela_help - changes the current directory of the process
 * @info: A structure that conatains arguments that will be
 * used functions and this format is applied to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int ela_help(ela_info *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

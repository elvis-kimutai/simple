#include "simples.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
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
 * change_dir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: Always 0
 */
int change_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1]) /* If no directory provided */
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* If the argument is '-' */
	{
		if (!_getenv(info, "OLDPWD=")) /* If the OLDPWD variable is not set */
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
		chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else /* If a directory path is provided */
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1) /* If the chdir command failed */
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else /* Update the PWD and OLDPWD environment variables */
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_help - displays the help message
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: Always 0
 */
int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

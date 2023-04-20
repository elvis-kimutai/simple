#include "main.h"

/**
 * exit_shell - Exit the shell with a given status code
 * @args: Parsed command arguments
 * @input: User input
 * @prog_name: Name of the program
 * @cmd_count: Count of executed commands
 * Return: Void (exits the shell)
 */
void exit_shell(char **args, char *input, char **prog_name, int cmd_count)
{
    int status, i = 0;

    if (args[1] == NULL)
    {
        free(input);
        free(args);
        exit(EXIT_SUCCESS);
    }

    while (args[1][i])
    {
        if (_isalphabetic(args[1][i++]) != 0)
        {
            _print_error(prog_name, cmd_count, args);
            break;
        }
        else
        {
            status = _atoi(args[1]);
            free(input);
            free(args);
            exit(status);
        }
    }
}

/**
 * change_directory - Change the current working directory
 * @args: Parsed command arguments
 * @last_status: Status of the last command executed
 * Return: 0 for success, 1 for failure
 */
int change_directory(char **args, __attribute__((unused)) int last_status)
{
    int ret_val = -1;
    char cwd[PATH_MAX];

    if (args[1] == NULL)
        ret_val = chdir(getenv("HOME"));
    else if (_strcmp(args[1], "-") == 0)
        ret_val = chdir(getenv("OLDPWD"));
    else
        ret_val = chdir(args[1]);

    if (ret_val == -1)
    {
        perror("my_shell");
        return (1);
    }
    else if (ret_val != -1)
    {
        getcwd(cwd, sizeof(cwd));
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    }

    return (0);
}

/**
 * display_env - Display environment variables
 * @args: Parsed command arguments
 * @last_status: Status of the last command executed
 * Return: 0 (always)
 */
int display_env(__attribute__((unused)) char **args, __attribute__((unused)) int last_status)
{
    size_t i;
    int len;

    for (i = 0; environ[i] != NULL; i++)
    {
        len = _strlen(environ[i]);
        write(STDOUT_FILENO, environ[i], len);
        write(STDOUT_FILENO, "\n", 1);
    }

    return (0);
}

/**

help_command - Displaying Help For Builtin

@args: Parsed Command

@status: Statue Of Last Command Excuted

Return: 0 Succes -1 Fail
*/
int help_command(char **args, attribute((unused)) int status)
{
int fd, fw, rd = 1;
char c;

fd = open(args[1], O_RDONLY);
if (fd < 0)
{
perror("Error");
return (0);
}
while (rd > 0)
{
rd = read(fd, &c, 1);
fw = write(STDOUT_FILENO, &c, rd);
if (fw < 0)
{
return (-1);
}
}
_putchar('\n');
return (0);
}

/**

execute_echo - Execute Echo Command Cases

@args: Parsed Command

@status: Statue Of Last Command Excuted

Return: Always 0 Or Excute Normal Echo
*/
int execute_echo(char **args, int status)
{
char *path;
unsigned int pid = getppid();

if (_strncmp(args[1], "$?", 2) == 0)
{
print_number_in(status);
PRINTER("\n");
}
else if (_strncmp(args[1], "$$", 2) == 0)
{
print_number(pid);
PRINTER("\n");

}
else if (_strncmp(args[1], "$PATH", 5) == 0)
{
path = _getenv("PATH");
PRINTER(path);
PRINTER("\n");
free(path);

}
else
return (print_echo(args));

return (1);
}

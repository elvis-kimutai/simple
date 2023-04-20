#include "main.h"

/**
 * handle_builtins - Handle Builtin Command
 * @command: Parsed Command
 * @status: Status of last Execution
 * Return: -1 Fail 0 Success (Return: Execute Builtin)
 */

int handle_builtins(char **command, int status)
{
    bul_t builtins[] = {
        {"cd", change_directory},
        {"env", display_environment},
        {"help", display_help},
        {"echo", echo_builtin},
        {"history", display_history},
        {NULL, NULL}
    };
    int i;

    for (i = 0; builtins[i].command != NULL; i++)
    {
        if (_strcmp(command[0], builtins[i].command) == 0)
        {
            return (builtins[i].function(command, status));
        }
    }

    return (-1);
}

/**
 * signal_handler - Handle ^C
 * @sig: Captured signal
 * Return: Void
 */
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		PRINTER("\n$ ");
	}
}

/**
 * execute_command - Execute Simple Shell Command (Fork, Wait, Execute)
 *
 * @command: Parsed Command
 * @user_input: User Input
 * @counter: Shell Execution Time Case of Command Not Found
 * @program_name: Program Name
 * Return: 1 Case Command Null, -1 Wrong Command, 0 Command Executed
 */
int execute_command(char **command, char *user_input, int counter, char **program_name)
{
	int status;
	pid_t pid;

	if (*command == NULL)
	{
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0)
	{
		if (_strncmp(*command, "./", 2) != 0 && _strncmp(*command, "/", 1) != 0)
		{
			add_path_to_command(command);
		}

		if (execve(*command, command, environ) == -1)
		{
			print_command_error(command[0], counter, program_name);
			free(user_input);
			free(command);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}

	wait(&status);
	return (0);
}

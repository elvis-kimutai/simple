#include "main.h"

/**
 * main - entry point
 *
 * Return: 0 on success, otherwise a positive error code.
 */
int main(void)
{
	char *input;
	char **args;
	int status;
	signal(SIGINT, handle_sigint);
	do
	{
		prompt();
		input = read_input();
		args = split_input(input);
		status = execute(args);
		free(input);
		free(args);
	}
	while(status);
	
	return (0);
}

/**
 * prompt - displays a prompt to the user
 */

void prompt(void)
{
	char *cwd = NULL;
	size_t size = 0;
	
	if (isatty(STDIN_FILENO))
	{
		cwd = getcwd(cwd, size);
		printf("#cisfun$ %s$ ", cwd);
	}
	else
	{
		printf("#cisfun$ ");
	}
	fflush(stdout);
	free(cwd);
}

/**
 * read_input - reads input from stdin
 *
 * Return: pointer to input string
 */
char *read_input(void)
{
	char *input = NULL;
	size_t size = 0;
	
	if (getline(&input, &size, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("\n");
		}
		free(input);
		exit(EXIT_SUCCESS);
	}
	return input;
}

/**
 * split_input - splits input string into array of arguments
 * @input: pointer to input string
 *
 * Return: array of arguments
 */

char **split_input(char *input)
{
	char **args;
	char *token;
	int i, n;
	n = 1;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == ' ')
		{
			n++;
		}
	}
	args = malloc((n + 1) * sizeof(char *));
	if (!args)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, " \n");
	i = 0;
	
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
	
	return args;
}

/**
 * execute - executes command with arguments
 * @args: array of arguments
 *
 * Return: 1 on success, 0 on failure
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	
	if (!args || !*args)
	{
		return 1;
	}
	pid = fork();
	
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return 1;
}

/**
 * handle_sigint - handles the interrupt signal (Ctrl + C)
 * @sig: signal number
 */
void handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	prompt();
	fflush(stdout);
}

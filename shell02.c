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

	signal(SIGINT, handle_sint);

	do {
		display_prompt();
		input = get_input();
		args = splt_input(input);
		status = exec(args);

		free(input);
		free(args);
	} while (status);

	return (0);
}

/**
 * display_prompt - displays a prompt to the user
 */
void display_prompt(void)
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
 * gets_input - reads input from stdin
 *
 * Return: pointer to input string
 */
char *get_input(void)
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

	return (input);
}

/**
 * splt_input - splits input string into array of arguments
 * @input: pointer to input string
 *
 * Return: array of arguments
 */
char **splt_input(char *input)
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

	return (args);
}

/**
 * exec - executes command with arguments
 * @args: array of arguments
 *
 * Return: 1 on success, 0 on failure
 */
int exec(char **args)
{
	pid_t pid;
	int status;

	if (!args || !*args)
	{
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (1);
}

/**
 * handle_sint - handles the interrupt signal (Ctrl + C)
 * @sig: signal number
 */
void handle_sint(int sig)
{
	(void) sig;
	printf("\n");
	display_prompt();
	fflush(stdout);
}

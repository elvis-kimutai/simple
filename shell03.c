#include "main.h"
/**
 * main - entry point
 * @argc: number of arguments passed to the program
 * @argv: array of pointers to strings containing the arguments
 *
 * Return: 0 on success, otherwise a positive error code.
 */
int main(int argc, char *argv[])
{
	char *input;
	char **args;
	int status;

	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0)
		{
		printf("Usage: %s\n", argv[0];
		printf("Simple Shell - A simple command-line shell.\n");
		printf("Options:\n");
		printf("  --help     Print this help message and exit.\n");
		return (0);
		}
		else if (strcmp(argv[1], "--version") == 0)
		{
		printf("Simple Shell - Version 1.0\n");
		return (0);
		}
		else
		{
		fprintf(stderr, "%s: invalid option '%s'\n", argv[0], argv[1]);
		fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
		return (EXIT_FAILURE);
		}
	}
	signal(SIGINT, handle_sigint);
	do {
		prompt();
		input = read_input();
		args = split_input(input);
		status = execute(args);
		free(input);
		free(args);
	}
	while (status);
	return (EXIT_SUCCESS);
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
	return (input);
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
	return (args);
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
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char cmd_path[1024];

	if (!args || !*args)
	{
		return (1);
	}
	if (!path)
	{
		printf("Error: PATH variable not set\n");
		return (1);
	}
	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, args[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				if (execve(cmd_path, args, environ) == -1)
				{
					perror("execve error");
					exit(EXIT_FAILURE);
				}
			}
		}
		waitpid(pid, &status, 0);
		free(path_copy);
		return (1);
	}
	dir = strtok(NULL, ":");
}
printf("Error: Command not found\n");
free(path_copy);
return (1);
}

/**
 * handle_sigint - handles the interrupt signal (Ctrl + C)
 * @sig: signal numbier
 */
void handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	prompt();
	fflush(stdout);
}

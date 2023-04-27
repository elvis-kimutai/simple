#include "main.h"

/**
 * prom - displays a prompt to the user
 */
void prom(void)
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
 * in_input - reads input from stdin
 *
 * Return: pointer to input string
 */
char *in_input(void)
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
 * cut_input - splits input string into array of arguments
 * @input: pointer to input string
 *
 * Return: array of arguments
 */
char **cut_input(char *input)
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
 * executes - executes command with arguments
 * @args: array of arguments
 *
 * Return: 1 on success, 0 on failure
 */
int executes(char **args)
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
/* Check if the command is "exit"*/
	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

/* Check if the PATH variable is set */
	if (!path)
	{
		printf("Error: PATH variable not set\n");
		return (0); /* Return 0 on failure*/
	}

	while (dir)
	{
		snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, args[0]);
		if (access(cmd_path, X_OK) == 0)
		{
/* The command exists, so we can execute it */
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
			else
			{
				waitpid(pid, &status, 0);
			}

			free(path_copy);
			return (1);
		}
		dir = strtok(NULL, ":"); /* Move the closing brace of if statement to here*/
	}

/* The command doesn't exist in the PATH */
	printf("Error: Command not found\n");
	free(path_copy);
	return (0); /* Return 0 on failure*/
}
/**
 * sort_sigint - handles the interrupt signal (Ctrl + C)
 * @sig: signal number
 */
void sort_sigint(int sig)
{
	(void) sig;
	printf("\n");
	prom();
	fflush(stdout);
}

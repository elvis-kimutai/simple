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

	signal(SIGINT, do_sigint);

	do {
		display_pro();
		input = in_put();
		args = argu_input(input);
		status = exec_argu(args);
		free(input);
		free(args);
	}
	while (status);

	return (0);
}
/**
 * display_pro - displays a prompt to the user
 */
void display_pro(void)
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
 * in_put - reads input from stdin
 *
 * Return: pointer to input string
 */
char *in_put(void)
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
 * argu_input - splits input string into array of arguments
 * @input: pointer to input string
 *
 * Return: array of arguments
 */
char **argu_input(char *input)
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
 * exec_argu - executes command with arguments
 * @args: array of arguments
 *
 * Return: 1 on success, 0 on failure
 */

int exec_argu(char **args)
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
	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env++);
		}
		return (1);
	}
	if (!path)
	{
		printf("Error: PATH variable not set\n");
		return (1);
	}
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
			else
			{
				waitpid(pid, &status, 0);
			}
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
 * do_sigint - handles the interrupt signal (Ctrl + C)
 * @sig: signal number
 */
void do_sigint(int sig)
{
	(void) sig;
	printf("\n");
	display_pro();
	fflush(stdout);
}

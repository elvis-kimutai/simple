#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

/**
 * main - Simple Unix command line interpreter
 *
 * Return: Always 0.
 */

int main(void)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_len;
	pid_t pid;

	while (1)
	{
	printf("%s", PROMPT);
	line_len = getline(&line, &line_size, stdin);

	if (line_len == -1)
	{
		putchar('\n');
		break;
	}
	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execl(line, line, (char *)NULL) == -1)
		{
		perror("Exec failed");
		exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
	}
	free(line);
	exit(EXIT_SUCCESS);
}

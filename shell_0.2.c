#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define PROMPT "#cisfun$ "
#define DELIM " \t\r\n\a"

int main(void)
{
    char *line = NULL;
    size_t line_size = 0;
    ssize_t line_len;
    pid_t pid;
    char *args[MAX_ARGS];
    int i;
    char *token;

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

        i = 0;
        token = strtok(line, DELIM);
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, DELIM);
        }
        args[i] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (execve(args[0], args, NULL) == -1)
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

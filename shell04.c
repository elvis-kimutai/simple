#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include   <sys/wait.h>

extern char **environ;                                                                                             
void prompt(void);
char *read_input(void);
char **split_input(char *input);
int execute(char **args);
void handle_sigint(int sig);

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

    do {
        prompt();
        input = read_input();
        args = split_input(input);
        status = execute(args);

        free(input);
        free(args);
    } while (status);

    return (0);
}

/**
 * prompt - displays a prompt to the user
 */
void prompt(void)
{
    char *cwd = NULL;
    size_t size = 0;

    if (isatty(STDIN_FILENO)) {
        cwd = getcwd(cwd, size);
        printf("#cisfun$ %s$ ", cwd);
    }
    else {
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

    if (getline(&input, &size, stdin) == -1) {
        if (isatty(STDIN_FILENO)) {
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
    for (i = 0; input[i]; i++) {
        if (input[i] == ' ') {
            n++;
        }
    }

    args = malloc((n + 1) * sizeof(char *));
    if (!args) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \n");
    i = 0;
    while (token) {
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

    if (!args || !*args) {
        return 1;
    }

    /* Check if the command is "exit"*/
    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    /* Check if the command exists in the PATH */
    char *path = getenv("PATH");
    if (!path) {
        printf("Error: PATH variable not set\n");
        return 1;
    }

    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    char cmd_path[1024];

    while (dir) {
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, args[0]);
        if (access(cmd_path, X_OK) == 0) {
            /* The command exists, so we can execute it */
            pid = fork();
            if (pid == -1) {
                perror("fork error");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                if (execve(cmd_path, args, environ) == -1) {
                    perror("execve error");
                    exit(EXIT_FAILURE);
                }
            } else {
                waitpid(pid, &status, 0);
            }

            free(path_copy);
            return 1;
        }
        dir = strtok(NULL, ":");
    }

    /* The command doesn't exist in the PATH */
    printf("Error: Command not found\n");
    free(path_copy);
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

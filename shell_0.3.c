#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 64
#define PROMPT "#cisfun$ "
#define DELIM " \t\r\n\a"

char *_getenv(const char *name);
char *_strdup(char *str);
char **_split(char *str, char *delim);
char *_which(char *cmd);

int main(void)
{
    char *line = NULL;
    size_t line_size = 0;
    ssize_t line_len;
    pid_t pid;
    char *args[MAX_ARGS];
    int i;
    char *token;
    char *cmd_path;

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

        cmd_path = _which(args[0]);
        if (cmd_path == NULL)
        {
            fprintf(stderr, "%s: command not found\n", args[0]);
            continue;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (execve(cmd_path, args, NULL) == -1)
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

/**
 * _getenv - Get an environment variable
 * @name: The name of the variable to get
 *
 * Return: The value of the variable, or NULL if not found
 */
char *_getenv(const char *name)
{
    extern char **environ;
    int i, j;

    for (i = 0; environ[i] != NULL; i++)
    {
        for (j = 0; name[j] != '\0'; j++)
            if (environ[i][j] != name[j])
                break;
        if (environ[i][j] == '=')
            return (&environ[i][j + 1]);
    }
    return (NULL);
}

/**
 * _strdup - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL if memory allocation fails
 */
char *_strdup(char *str)
{
    char *new_str;
    int i, len = 0;

    while (str[len])
        len++;

    new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
        return (NULL);

    for (i = 0; str[i]; i++)
        new_str[i] = str[i];

    new_str[len] = '\0';
    return (new_str);
}

/**
 * _split - Split a string into an array of strings
 * @str: The string to split
 * @delim: The delimiter to split on
 *
 * Return: Pointer to the array of strings, or NULL if memory allocation fails
 */

char **_split(char *str, char *delim)
{
    char **array;
    int i, count = 0;
    char *token;

    str = _strdup(str);
    if (str == NULL)
        return (NULL);

    token = strtok(str, delim);
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, delim);
    }

    free(str);

    array = malloc(sizeof(char *) * (count + 1));
    if (array == NULL)
        return (NULL);

    str = _strdup(str);
    if (str == NULL)
        return (NULL);

    token = strtok(str, delim);
    for (i = 0; token != NULL; i++)
    {
        array[i] = _strdup(token);
        token = strtok(NULL, delim);
    }
    array[i] = NULL;

    free(str);

    return (array);
}

/**
 * _which - Find the full path of a command
 * @cmd: The command to find
 *
 * Return: Pointer to the full path of the command, or NULL if not found
 */
char *_which(char *cmd)
{
    char *path, **dirs;
    char *cmd_path;
    int i;
    struct stat st;

    if (cmd[0] == '/')
        return (_strdup(cmd));

    path = _getenv("PATH");
    if (path == NULL)
        return (NULL);

    dirs = _split(path, ":");
    if (dirs == NULL)
        return (NULL);

    cmd_path = malloc(sizeof(char) * (strlen(cmd) + strlen(path) + 2));
    if (cmd_path == NULL)
        return (NULL);

    for (i = 0; dirs[i] != NULL; i++)
    {
        strcpy(cmd_path, dirs[i]);
        strcat(cmd_path, "/");
        strcat(cmd_path, cmd);
        if (stat(cmd_path, &st) == 0 && st.st_mode & S_IXUSR)
            break;
    }

    free(dirs);

   if (dirs[i] == NULL)
        return (NULL);

    return (_strdup(cmd_path));
}

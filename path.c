#include "main.h"
/**
 * getenv_value - Gets the value of an environment variable by name
 * @name: Environment variable name
 * Return: The value of the environment variable else NULL.
 */
char *getenv_value(char *name)
{
    size_t name_length, value_length;
    char *value_ptr;
    int idx, char_idx, value_idx;

    name_length = strlen(name);
    for (idx = 0; environ[idx] != NULL; ++idx)
    {
        if (strncmp(name, environ[idx], name_length) == 0)
        {
            value_length = strlen(environ[idx]) - name_length;
            value_ptr = malloc(sizeof(char) * (value_length + 1));
            if (!value_ptr)
            {
                perror("Unable to allocate memory for environment variable value");
                return (NULL);
            }

            value_idx = 0;
            for (char_idx = name_length + 1; environ[idx][char_idx] != '\0'; ++char_idx, ++value_idx)
            {
                value_ptr[value_idx] = environ[idx][char_idx];
            }
            value_ptr[value_idx] = '\0';

            return (value_ptr);
        }
    }

    return (NULL);
}

/**
 * add_path_to_command - Search in $PATH for executable command
 * @command: Parsed input
 * Return: 1 on failure, 0 on success
 */

int add_path_to_command(char **command)
{
        char *path, *dir, *cmd_path;
        struct stat buf;

        path = getenv_value("PATH");
        dir = _strtok(path, ":");
        while (dir != NULL)
        {
                cmd_path = build_path(*command, dir);
                if (stat(cmd_path, &buf) == 0)
                {
                        *command = _strdup(cmd_path);
                        free(cmd_path);
                        free(path);
                        return (0);
                }
                free(cmd_path);
                dir = _strtok(NULL, ":");
        }
        free(path);

        return (1);
}
/**
 * build_path - Build command path
 * @command: Command name
 * @directory: Directory containing command
 *
 * Return: Parsed full path of command or NULL if failed
 */
char *build_path(char *command, char *directory)
{
        char *cmd_path;
        size_t len;
        int i, j;

        len = _strlen(directory) + _strlen(command) + 2;
        cmd_path = malloc(sizeof(char) * len);
        if (cmd_path == NULL)
        {
                return (NULL);
        }

        memset(cmd_path, 0, len);

        for (i = 0; i < _strlen(directory); i++)
        {
                cmd_path[i] = directory[i];
        }

        cmd_path[i++] = '/';
        for (j = 0; command[j] != '\0'; i++, j++)
        {
                cmd_path[i] = command[j];
        }
        cmd_path[i] = '\0';

        return (cmd_path);
}

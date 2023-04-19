#include "main.h"

/**
 * has_delimiter - Checks if a character matches any delimiter character
 *
 * @ch: Character to check
 * @delimiter: Delimiter string
 * Return: 1 if match found, 0 if not
 */
unsigned int has_delimiter(char ch, const char *delimiter)
{
	unsigned int index;
       for (index = 0; delimiter[index] != '\0'; index++)
    {
        if (ch == delimiter[index])
        {
            return (1);
        }
    }
    return (0);
}
/**
 * custom_strtok - Tokenizes a string into tokens
 *
 * @str: String to tokenize
 * @delimiter: Delimiter string
 * Return: Pointer to the next token or NULL if no more tokens
 */
char *custom_strtok(char *str, const char *delimiter)
{
    static char *saved_str;
    static char *next_token;
    unsigned int index;

    if (str != NULL)
    {
        next_token = str;
    }
    saved_str = next_token;

    if (saved_str == NULL)
    {
        return (NULL);
    }

    for (index = 0; saved_str[index] != '\0'; index++)
    {
        if (has_delimiter(saved_str[index], delimiter) == 0)
        {
            break;
        }
    }

    if (next_token[index] == '\0' || next_token[index] == '#')
    {
        next_token = NULL;
        return (NULL);
    }

    saved_str = next_token + index;
    next_token = saved_str;

    for (index = 0; next_token[index] != '\0'; index++)
    {
        if (has_delimiter(next_token[index], delimiter) == 1)
        {
            break;
        }
    }

    if (next_token[index] == '\0')
    {
        next_token = NULL;
    }
    else
    {
        next_token[index] = '\0';
        next_token = next_token + index + 1;
        if (*next_token == '\0')
        {
            next_token = NULL;
        }
    }

    return (saved_str);
}

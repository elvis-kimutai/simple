#include "main.h"

/**
 * _strncpy - copies a string
 * @dest_str: pointer to the destination string
 * @src_str: pointer to the source string
 * @num_chars: number of characters to copy
 *
 * Return: a pointer to the destination string
 */
char *_strncpy(char *dest_str, const char *src_str, size_t num_chars)
{
    size_t index;

    for (index = 0; index < num_chars && src_str[index]; index++)
    {
        dest_str[index] = src_str[index];
    }
    for (; index < num_chars; index++)
    {
        dest_str[index] = '\0';
    }

    return dest_str;
}

/**
 * _strlen - returns the length of a string
 * @str: pointer to the string to measure
 *
 * Return: the length of the string
 */

int _strlen(const char *str)
{
    int len = 0;

    while (*str != '\0')
    {
        len++;
        str++;
    }

    return len;
}

/**
 * _atoi - converts a string to an integer
 * @str: the string to convert
 *
 * Return: the integer value of the string
 */
int _atoi(char *str)
{
    int index, num = 0, sign = 1;

  
    for (index = 0; str[index] != '\0' && (str[index] < '0' || str[index] > '9'); index++)
    {
        if (str[index] == '-')
        {
            sign = -1;
        }
    }
    for (; str[index] >= '0' && str[index] <= '9'; index++)
    {
        num = (num * 10) + sign * (str[index] - '0');
    }

    return num;
}
/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	return (write(1, &ch, 1));
}

/**
 * _put - prints a string
 * @s: pointer to the string to print
 *
 * Return: void
 */
void _put(char *s)
{
    int idx;

    for (idx = 0; s[idx] != '\0'; idx++)
    {
        _putchar(s[idx]);
    }

    _putchar('\n');
}

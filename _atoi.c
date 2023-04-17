#include "shell.h"

/**
 * check_delimiter - checks if character is a delimiter
 * @character: the char to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int check_delimiter(char character, char *delimiter)
{
    int i;
    for (i = 0; delimiter[i]; i++)
    {
        if (delimiter[i] == character)
            return (1);
    }
    return (0);
}
int is_alphabetic(int character)
{
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) ? 1 : 0;
}

/**
 * string_to_int - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *string)//atoi function
{
    int index;
    int sign = 1;
    int flag = 0;
    int output_value;
    unsigned int result = 0;

    for (index = 0; string[index] != '\0' && flag != 2; index++)
    {
        if (string[index] == '-')
            sign *= -1;

        if (string[index] >= '0' && string[index] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (string[index] - '0');
        }
        else if (flag == 1)
		flag = 2;
    }

    output_value = sign == -1 ? -result : result;

    return (output_value);
}

/**
 * is_interactive_mode - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive_mode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

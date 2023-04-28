#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <sys/wait.h>
/**
 * custom_getline - reads a line of input from the user
 *
 * Description: This function reads input from the user using a buffer to
 * minimize calls to the read system call. It dynamically allocates memory to
 * store the input and returns a pointer to the input string.
 *
 * Return: pointer to input string, or NULL on failure
 */

#define BUFFER_SIZE 1024

char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int position;
	static int length;

	char *line = NULL;
	int line_length = 0;
	int c;

	while (1)
	{
	/* Check if we need to read more data into the buffer*/
		if (position >= length)
		{
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			position = 0;

			/* End of file or error*/
			if (length == 0 || length == -1)
			{
				return (NULL);
			}
		}

		/* Read the next character from the buffer*/
		c = buffer[position++];

		/* Check if we've reached the end of the line */
		if (c == '\n' || c == '\r')
		{
			break;
		}

	/* Append the character to the line*/
		if (line_length == 0)
		{
			line = malloc(sizeof(char));
		}
		else
		{
			line = realloc(line, (line_length + 1) * sizeof(char));
		}

		line[line_length++] = c;
	}

	/* Append a null terminator to the line*/
	if (line_length > 0)
	{
		line = realloc(line, (line_length + 1) * sizeof(char));
		line[line_length] = '\0';
	}

	return (line);
}

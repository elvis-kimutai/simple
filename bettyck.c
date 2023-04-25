#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int y, x;

	for (y = 1; y <= 10; y++)
	{
		for (x = 1; x <= y; x++)
		{
			printf("%d ", x);
		}
		printf("\n");
	}

	return (EXIT_SUCCESS);
}

#include "main.h"

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
	signal(SIGINT, handle_sint);
	signal(SIGINT, run_sigint);
	signal(SIGINT, sort_sigint);
	signal(SIGINT, do_sigint);

	do {
		prompt();
		input = read_input();
		args = split_input(input);
		status = execute(args);

		display_prompt();
		input = get_input();
		args = splt_input(input);
		status = exec(args);

		dis_prompt();
		input = show_input();
		args = div_input(input);
		status = exe(args);

		prom();
		input = in_input();
		args = cut_input(input);
		status = executes(args);

		display_pro();
		input = in_put();
		args = argu_input(input);
		status = exec_argu(args);

		free(input);
		free(args);
	} while (status);
	return (0);
}

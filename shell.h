#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>

#define PRINTER(...) fprintf(stdout, __VA_ARGS__)
extern char **environ;

/* main.c */
int main(void);
/* shell_helpers.c */
void print_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args, char *input, char **prog_name, int cmd_count);
/* builtin_commands.c */
void exit_shell(char **args, char *input, char **prog_name, int cmd_count);
int change_directory(char **args, int last_status);
int display_env(char **args, int last_status);
int help_command(char **args, int status);
int execute_echo(char **args, int status);

/*stringstoken.c*/
unsigned int has_delimiter(char ch, const char *delimiter);
char *custom_strtok(char *str, const char *delimiter);
/*char.c*/
char *_strncpy(char *dest_str, const char *src_str, size_t num_chars);
int _strlen(const char *str);
int _atoi(char *str);
int _putchar(char ch);
void _put(char *s);
/* string_helpers.c */
int _puts(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n)
char *_strcat(char *dest, char *src);
int _isnumeric(char *str);
int _isalphabetic(char c);
void print_number(int n);
void print_number_in(int n);
/*path.c*/
char *getenv_value(char *name);
int add_path_to_command(char **command);
char *build_path(char *command, char *directory);
/*run.c*/
void add_path_to_command(char **command);
void print_command_error(char *command, int counter, char **program_name);
/* builtins.c */
typedef struct bul
{
        char *command;
        int (*function)(char **command, int status);
} bul_t;
int handle_builtins(char **command, int status);
int change_directory(int argc, char **argv);
int display_environment(char **command, int status);
int display_help(char **command, int status);
int echo_builtin(char **command, int status);
int display_history(char **command, int status);
/* shell_loop.c */
void shell_loop(char **env);

#endif /* MAIN_H */ 


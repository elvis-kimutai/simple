#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>
#include <limits.h>

#define DELIMITER " \t\r\n\a"
/* st */
unsigned int has_delimiter(char ch, const char *delimiter);
char *custom_strtok(char *str, const char *delimiter);

/* exit */
/* exit */
void exit_shell(char **args, char *input, char **prog_name, int cmd_count);
int change_directory(char **args, __attribute__((unused)) int last_status);
int display_env(__attribute__((unused)) char **args, __attribute__((unused)) int last_status);
int help_command(char **args, __attribute__((unused)) int status);
int execute_echo(char **args, int status);

/** str */
int _isalphabetic(int c);
void _print_error(char **prog_name, int cmd_count, char **args);
int _strcmp(char *s1, char *s2);
char *_getenv(const char *name);
int print_echo(char **args);
void print_number(int n);
void print_number_in(int n);
int _strncmp(const char *s1, const char *s2, size_t n);
extern char **environ;
int display_env(char **args, int last_status);
/*size_t _strlen(char *s);*/
int _putchar(char c);

/*chr file*/

char *_strncpy(char *dest_str, const char *src_str, size_t num_chars);
int _strlen(const char *str);
int _atoi(char *str);
int _putchar(char ch);
void _puts(char *s);

#endif

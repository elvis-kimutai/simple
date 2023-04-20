#ifndef _SHELL_H_
#define _SHELL_H_

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

#define DELIMITER " \t\r\n\a"

unsigned int has_delimiter(char ch, const char *delimiter);
char *custom_strtok(char *str, const char *delimiter);



/*chr file*/

char *_strncpy(char *dest_str, const char *src_str, size_t num_chars);
int _strlen(const char *str);
int _atoi(char *str);
int _putchar(char ch);
void _puts(char *s);

#endif

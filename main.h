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
/* st */
unsigned int has_delimiter(char ch, const char *delimiter);
char *custom_strtok(char *str, const cha *delimiter);




#endif

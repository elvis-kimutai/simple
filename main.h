#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void prompt(void);
char *read_input(void);
char **split_input(char *input);
int execute(char **args);
void handle_sigint(int sig);
extern char **environ;

#ifndef MAIN_H
#define MAIN_H

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

void display_prompt(void);
char *get_input(void);
char **splt_input(char *input);
int exec(char **args);
void handle_sint(int sig);

void dis_prompt(void);
char **div_input(char *input);
int exe(char **args);
char *show_input(void);
void run_sigint(int sig);

void prom(void);
char *in_input(void);
char **cut_input(char *input);
int executes(char **args);
void sort_sigint(int sig);

void display_pro(void);
char *in_put(void);
char **argu_input(char *input);
int exec_argu(char **args);
void do_sigint(int sig);

char *custom_getline(void);
#endif

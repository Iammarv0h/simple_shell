#ifndef MAIN_H
#define MAIN_H
#define MAX_ARGS 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execmd(char **argv);

int parse_input(char *input, char **args);

char *get_location(char *command);

char *custom_getline(void);

int shell_setenv(char **args);

int shell_unsetenv(char **args);

#endif /* MAIN_H */

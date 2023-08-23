#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/* Function to parse input into arguments*/
int parse_input(char* input, char** args);

/* Function for built-in commands*/
void execute_builtin_commands(char** args);

/* Function for executing external commands*/
void execute_external_commands(char** args);

/* Function for piping commands*/
void execute_piped_commands(char* pipe_commands[], int pipe_count);

/*Function for input redirection*/
int redirect_input(char** args);

/*Function for output redirection*/
int redirect_output(char** args);

#endif /* SHELL_H */

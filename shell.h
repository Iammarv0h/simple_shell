#ifndef SHELL_H
#define SHELL_H

// Function to parse input into arguments
int parse_input(char* input, char** args);

// Function for built-in commands
void execute_builtin_commands(char** args);

// Function for executing external commands
void execute_external_commands(char** args);

// Function for piping commands
void execute_piped_commands(char* pipe_commands[], int pipe_count);

// Function for input redirection
int redirect_input(char** args);

// Function for output redirection
int redirect_output(char** args);

#endif /* SHELL_H */

#include "shell.h"

int parse_input(char *input, char **args) {
    const char *delim = " \n";
    char *token;
    int arg_count = 0;

    /* Get the first token */
    token = strtok(input, delim);

    /* Walk through other tokens */
    while (token != NULL) {
        /* Allocate space for the token and store it in args array */
        args[arg_count] = malloc(strlen(token) + 1);
        strcpy(args[arg_count], token);

        /* Increment argument count */
        arg_count++;

        /* Get the next token */
        token = strtok(NULL, delim);
    }

    /* Null-terminate the args array */
    args[arg_count] = NULL;

    return (arg_count);
}

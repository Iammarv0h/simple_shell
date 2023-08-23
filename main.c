#include "shell.h"

int parse_input(char *input, char **args);

int main(int argc, char **argv) {
    char *prompt = "(simple_shell $ ";
    char *lineptr;
    size_t n = 0;
    ssize_t nchars_read;

    /* Declare the array to store command arguments */
    char *args[MAX_ARGS];

    /* Ignore unused parameters */
    (void)argc;
    (void)argv;

    /* Create an infinite loop */
    while (1) {
        int arg_count; /* Declare arg_count here */

        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);

        /* Check if the getline function failed or reached EOF or user used CTRL + D */
        if (nchars_read == -1) {
            printf("Exiting shell....\n");
            return (-1);
        }

        /* Parse input into arguments */
        arg_count = parse_input(lineptr, args);

        /* Execute the command */
        if (arg_count > 0) {
            execmd(args);
        }

        /* Free up allocated memory */
        free(lineptr);
    }

    return (0);
}

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

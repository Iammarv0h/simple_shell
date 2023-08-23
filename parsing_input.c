#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * parse_input - Function to parse input into arguments
 * @input: The input string to be parsed
 * @args: An array to store the parsed arguments
 *
 * Return: The number of parsed arguments
 */
int parse_input(char *input, char **args)
{
    int arg_count = 0;

    /* Use strtok to split the input into arguments */
    char *token = strtok(input, " \t\n");
    while (token != NULL && arg_count < MAX_ARGS - 1)
    {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL; /* Null-terminate the argument list */

    return (arg_count); /* Return the number of arguments */
}

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    while (1)
    {
        char input[MAX_INPUT_SIZE];

        printf("MyShell> "); /* Prompt user for input */

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0'; /* Remove newline character */

        /* Parse input into arguments */
        char *args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        printf("Parsed arguments:\n");
        for (int i = 0; i < arg_count; i++)
        {
            printf("args[%d]: %s\n", i, args[i]); /* Print parsed arguments */
        }

        if (strcmp(input, "exit") == 0)
        {
            break; /* Exit the loop if "exit" is entered */
        }
    }

    return (0); /* Exit the program */
}


#include "shell.h"

/**
 * parse_input - Parse the input line into an array of arguments
 * @input: The input line
 * @args: The array to store the arguments
 *
 * This function tokenizes the input line into separate arguments.
 * It also handles skipping lines starting with '#' (comments).
 *
 * Return: The number of arguments
 */

int parse_input(char *input, char **args)
{
    int arg_count = 0;
    char *token = strtok(input, " \t\n");

    while (token)
    {
        if (token[0] != '#') /*Skip lines starting with '#'*/
        {
            args[arg_count++] = token;
        }
        token = strtok(NULL, " \t\n");
    }

    return arg_count;
}


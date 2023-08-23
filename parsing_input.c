#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int parse_input(char *input, char **args)
{
    int arg_count = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL && arg_count < MAX_ARGS - 1)
    {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL;
    return arg_count;
}

int main(void)
{
    while (1)
    {
        char input[MAX_INPUT_SIZE];

        printf("MyShell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        char *args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        printf("Parsed arguments:\n");
        for (int i = 0; i < arg_count; i++)
        {
            printf("args[%d]: %s\n", i, args[i]);
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}

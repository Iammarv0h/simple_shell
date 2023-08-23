#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int parse_input(char *input, char **args);

/**
 * main - Entry point for the shell
 *
 * Return: Always 0
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    int arg_count;

    while (1)
    {
        printf("MyShell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        arg_count = parse_input(input, args);

        if (arg_count > 0)
        {
            if (strcmp(args[0], "exit") == 0)
            {
                break;
            }
            else if (strcmp(args[0], "cd") == 0)
            {
                if (arg_count > 1)
                {
                    if (chdir(args[1]) != 0)
                    {
                        perror("cd");
                    }
                }
                continue;
            }
        }

        /* Implement command execution here using execve()*/

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}

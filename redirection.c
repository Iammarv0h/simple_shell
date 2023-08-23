#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * parse_input - Parse input into arguments
 * @input: Input string
 * @args: Array to store arguments
 *
 * Return: Number of arguments
 */
int parse_input(char *input, char **args);

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

        /* Parse input into arguments*/
        char *args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        if (arg_count > 0)
        {
            /*Handle built-in commands (same as before)*/
        }

        /* Implement input and output redirection*/
        int input_fd = STDIN_FILENO;
        int output_fd = STDOUT_FILENO;

        /* Check for input redirection*/
        int i;
        for (i = 0; i < arg_count; i++)
        {
            if (strcmp(args[i], "<") == 0)
            {
                args[i] = NULL;
                i++;
                input_fd = open(args[i], O_RDONLY);
                if (input_fd == -1)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }

        /* Check for output redirection*/
        for (i = 0; i < arg_count; i++)
        {
            if (strcmp(args[i], ">") == 0)
            {
                args[i] = NULL;
                i++;
                output_fd = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_fd == -1)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }

        /* Fork and execute the command*/
        pid_t pid = fork();
        if (pid == 0)
        {
            /* Child process*/
            dup2(input_fd, STDIN_FILENO);
            dup2(output_fd, STDOUT_FILENO);

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
        }
        else
        {
            /*Parent process*/
            waitpid(pid, NULL, 0);
        }

        /* Close file descriptors*/
        if (input_fd != STDIN_FILENO)
        {
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO)
        {
            close(output_fd);
        }

        if (strcmp(args[0], "exit") == 0)
        {
            /* Clean up and exit*/
            break;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * parse_input - Parse input into arguments
 * @input: Input string
 * @args: Array to store arguments
 *
 * Return: Number of arguments
 */
int parse_input(char *input, char **args)
{
    // ... (implementation as before)
}


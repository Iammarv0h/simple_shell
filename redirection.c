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

/**
 * main - Main function for the shell
 * 
 * Return: Always 0
 */
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

        /* Parse input into arguments */
        char *args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        if (arg_count > 0)
        {
            if (strcmp(args[0], "exit") == 0)
            {
                /* Exit the shell */
                printf("Exiting the shell...\n");
                break;
            }

            /* Fork a new process */
            pid_t child_pid = fork();

            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (child_pid == 0)
            {
                /* Child process code */

                /* Execute the command */
                execvp(args[0], args);

                /* If execvp returns, there was an error */
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            else
            {
                /* Parent process code */

                /* Wait for the child process to complete */
                int child_status;
                waitpid(child_pid, &child_status, 0);

                if (WIFEXITED(child_status))
                {
                    printf("Child process exited with status: %d\n", WEXITSTATUS(child_status));
                }
                else
                {
                    printf("Child process did not exit normally.\n");
                }
            }
        }
    }

    return (0);
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
    int arg_count = 0;
    char *token = strtok(input, " ");

    while (token != NULL && arg_count < MAX_ARGS - 1)
    {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " ");
    }

    args[arg_count] = NULL; /* Set the last element to NULL for execvp */
    return (arg_count);
}


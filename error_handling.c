#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * parse_input - Parse input into arguments
 * @input: Input string
 * @args: Argument array
 * Return: Number of arguments
 */
int parse_input(char *input, char **args)
{
    int arg_count = 0;
    // ... (implementation of parse_input as before)
    return arg_count;
}

/**
 * main - Entry point for the shell with error handling
 * Return: 0 on success, otherwise error code
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

        char *args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        if (arg_count > 0)
        {
            // Handle built-in commands
            if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }
            else if (strcmp(args[0], "cd") == 0)
            {
                // ... (handle cd command)
            }
            // ... (handle other built-in commands)
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE); // Added this line to exit child process
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0)
                {
                    fprintf(stderr, "MyShell: %s: Exit status %d\n", args[0], exit_status);
                }
            }
            else if (WIFSIGNALED(status))
            {
                int signal_num = WTERMSIG(status);
                fprintf(stderr, "MyShell: %s: Terminated by signal %d\n", args[0], signal_num);
            }
        }
    }

    return 0;
}


#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Description: This function implements a basic Unix shell that reads
 * commands from the user, executes them, and displays the results.
 * It provides a prompt, reads user input, processes the input,
 * and executes the appropriate command.
 *
 * Return: Always 0
 */

int main(void)
{
	char *prompt = "(simple_shell $ ";
	char *lineptr;
	char *args[MAX_ARGS];

	while (1)
	{
		int arg_count;

		printf("%s", prompt);
		lineptr = custom_getline();

		if (lineptr == NULL)
		{
			printf("Exiting shell....\n");
			return (-1);
		}

		arg_count = parse_input(lineptr, args);
		if (arg_count > 0)
		{
			if (strcmp(args[0], "setenv") == 0)
			{
				shell_setenv(args);
			}
			else if (strcmp(args[0], "unsetenv") == 0)
			{
				shell_unsetenv(args);
			}
			else
			{
				execmd(args);
			}
		}
		free(lineptr);
	}
	return (0);
}

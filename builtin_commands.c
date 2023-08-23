#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * parse_input - Function to parse input into arguments
 * @input: Input string to be parsed
 * @args: Array to store parsed arguments
 *
 * Return: Number of parsed arguments
 */
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
	args[arg_count] = NULL; /* Null-terminate the argument list */

	return (arg_count); /* Return the number of arguments */
}

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	while (1)
	{
		char input[MAX_INPUT_SIZE];
		char *args[MAX_ARGS];
		int arg_count;

		printf("Shell> "); /* Print the shell prompt */
		fgets(input, sizeof(input), stdin); /* Read input from the user */

		/* Remove the newline character at the end of input */
		input[strcspn(input, "\n")] = '\0';

		/* Parse the input into arguments */
		arg_count = parse_input(input, args);

		/* Check if the user entered any command */
		if (arg_count > 0)
		{
			/* Implement your code to handle the commands here */

			/* For now, let's just print the parsed arguments */
			for (int i = 0; i < arg_count; i++)
			{
				printf("Argument %d: %s\n", i, args[i]);
			}
		}
	}

	return (0);
}


#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*Add this line*/

/**
 * builtin_exit - Handle the built-in exit command with optional status.
 * @input: The input string containing the command and optional status.
 */

void builtin_exit(char *input)
{
	if (strncmp(input, "exit ", 5) == 0)
	{
		int exit_status = atoi(input + 5);

		free(input);
		exit(exit_status);
	}
}

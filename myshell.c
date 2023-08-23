#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

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

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}

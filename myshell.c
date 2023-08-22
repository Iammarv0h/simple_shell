#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

int main() {
    while (1) {
        char input[MAX_INPUT_SIZE];

        printf("MyShell> ");
        
        // Read input using fgets to avoid buffer overflow
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Process the input and implement command execution here

        // Break the loop if the user types "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}

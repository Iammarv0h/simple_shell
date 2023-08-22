#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

// Function to parse input into arguments
int parse_input(char* input, char** args) {
    int arg_count = 0;
    
    // Use strtok to split the input into arguments
    char* token = strtok(input, " \t\n");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL; // Null-terminate the argument list
    
    return arg_count; // Return the number of arguments
}

int main() {
    while (1) {
        char input[MAX_INPUT_SIZE];

        printf("MyShell> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        // Parse input into arguments
        char* args[MAX_ARGS];
        int arg_count = parse_input(input, args);

        if (arg_count > 0) {
            // Handle built-in commands
            if (strcmp(args[0], "exit") == 0) {
                // Exit the shell
                break;
            } else if (strcmp(args[0], "cd") == 0) {
                // Change directory
                if (arg_count > 1) {
                    if (chdir(args[1]) != 0) {
                        perror("cd");
                    }
                }
                continue; // Skip command execution for "cd"
            }
        }

        // Print the parsed arguments (for demonstration purposes)
        printf("Parsed arguments:\n");
        for (int i = 0; i < arg_count; i++) {
            printf("args[%d]: %s\n", i, args[i]);
        }

        // Implement command execution here using execve()

        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}

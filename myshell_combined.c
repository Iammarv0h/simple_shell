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

// Function to parse input into arguments (same as before)
int parse_input(char* input, char** args) {
    // ... (unchanged)
}

// Function to handle built-in commands (same as before)
void execute_builtin_commands(char** args) {
    // ... (unchanged)
}

// Function to execute external commands using execve()
void execute_external_commands(char** args) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execve(args[0], args, NULL);
        perror(args[0]); // This line will only execute if execve fails
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
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
            execute_builtin_commands(args);

            // Execute external commands using execve()
            execute_external_commands(args);

            if (strcmp(input, "exit") == 0) {
                break;
            }
        }
    }

    return 0;
}


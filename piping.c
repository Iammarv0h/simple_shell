#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

// Function to parse input into arguments (same as before)
int parse_input(char* input, char** args) {
    // ... (unchanged)
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
            // Handle built-in commands (same as before)
        }

        // Implement piping functionality
        char* command = args[0];
        int pipe_count = 0;
        char* pipe_commands[MAX_ARGS];
        
        // Split input into separate commands using pipes
        char* token = strtok(input, "|");
        while (token != NULL && pipe_count < MAX_ARGS) {
            pipe_commands[pipe_count] = token;
            pipe_count++;
            token = strtok(NULL, "|");
        }

        // Create a series of pipes
        int pipes[MAX_ARGS - 1][2];
        for (int i = 0; i < pipe_count - 1; i++) {
            if (pipe(pipes[i]) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        // Fork and execute piped commands
        for (int i = 0; i < pipe_count; i++) {
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                if (i != 0) {
                    dup2(pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from previous pipe
                    close(pipes[i - 1][0]);
                }
                if (i != pipe_count - 1) {
                    dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to the current pipe
                    close(pipes[i][0]);
                }

                // Execute the command
                args[0] = strtok(pipe_commands[i], " \t\n");
                execvp(command, args);
                perror("execvp"); // This line will only execute if execvp fails
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                perror("fork");
            }

            // Close pipes in parent process
            if (i != 0) {
                close(pipes[i - 1][0]);
            }
            if (i != pipe_count - 1) {
                close(pipes[i][1]);
            }
        }

        // Close remaining pipes in parent process
        for (int i = 0; i < pipe_count - 1; i++) {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }

        // Wait for all child processes to complete
        for (int i = 0; i < pipe_count; i++) {
            wait(NULL);
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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

        // Implement input and output redirection (same as before)

        // Fork and execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror(args[0]); // Print error message similar to Linux shell
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            // Check if the child exited normally
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    fprintf(stderr, "MyShell: %s: Exit status %d\n", args[0], exit_status);
                }
            } else if (WIFSIGNALED(status)) {
                int signal_num = WTERMSIG(status);
                fprintf(stderr, "MyShell: %s: Terminated by signal %d\n", args[0], signal_num);
            }
        }

        // Close file descriptors (same as before)

        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}

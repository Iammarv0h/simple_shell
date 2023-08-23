#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

void execmd(char **argv) {
    if (argv) {
        char *command = argv[0];
        char *actual_command = get_location(command);

        if (actual_command) {
            pid_t child_pid = fork();
            if (child_pid == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                /* Child process */
                execve(actual_command, argv, NULL);
                perror("Error executing command");
                exit(EXIT_FAILURE);
            } else {
                /* Parent process */
                int status;
                waitpid(child_pid, &status, 0);

                /* Free memory */
                free(actual_command);
            }
        } else {
            printf("Command not found: %s\n", command);
        }
    }
}

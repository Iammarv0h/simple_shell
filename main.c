#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int main(void) {
    char *line = NULL;
    size_t len = 0;
    pid_t pid;
    char *args[MAX_INPUT_LENGTH];
    char *token;
    int i = 0;

    while (1) {
        printf("$ ");

        if (getline(&line, &len, stdin) == -1) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        i = 0;
        token = strtok(line, " ");

        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                _exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(line);
    }

    return 0;
}

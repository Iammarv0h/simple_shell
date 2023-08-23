#include "shell.h"

int shell_setenv(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return (1);
    }

    if (setenv(args[1], args[2], 1) == -1) {
        perror("setenv");
        return (1);
    }

    return (0);
}

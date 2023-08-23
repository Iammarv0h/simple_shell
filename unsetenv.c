#include "shell.h"

int shell_unsetenv(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return (1);
    }

    if (unsetenv(args[1]) == -1) {
        perror("unsetenv");
        return (1);
    }

    return (0);
}

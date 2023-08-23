#include "shell.h"

int main(void) {
    char *prompt = "(simple_shell $ ";
    char *lineptr;
    char *args[MAX_ARGS];

    while (1) {
        int arg_count;

        printf("%s", prompt);
        lineptr = custom_getline();

        if (lineptr == NULL) {
            printf("Exiting shell....\n");
            return (-1);
        }

        arg_count = parse_input(lineptr, args);

        if (arg_count > 0) {
            execmd(args);
        }

        free(lineptr);
    }

    return (0);
}

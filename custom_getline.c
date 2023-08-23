#include "shell.h"

#define BUFFER_SIZE 1024

char *custom_getline(void) {
    static char buffer[BUFFER_SIZE];
    static size_t pos = 0;
    static ssize_t len = 0; /* Use ssize_t for read return value*/

    char *line = NULL;
    size_t line_len = 0;

    while (1) {
        char c; /* Move the declaration of 'c' here*/

        if (pos >= (size_t)len) {
            len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            pos = 0;

            if (len == 0) {
                if (line_len == 0) {
                    return (NULL);
                } else {
                    break;
                }
            } else if (len == (ssize_t)-1) {
                perror("read");
                return (NULL);
            }
        }

        c = buffer[pos++];
        if (c == '\n') {
            break;
        }

        line = realloc(line, line_len + 2);
        if (line == NULL) {
            perror("realloc");
            return (NULL);
        }
        line[line_len++] = c;
        line[line_len] = '\0';
    }

    return (line);
}

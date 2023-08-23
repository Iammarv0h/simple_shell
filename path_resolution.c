#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char *get_location(char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    if (path_copy) {
        command_length = strlen(command);

        path_token = strtok(path_copy, ":");

        while (path_token != NULL) {
            directory_length = strlen(path_token);
            file_path = malloc(command_length + directory_length + 2);
            if (file_path == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");

            if (stat(file_path, &buffer) == 0) {
                free(path_copy);
                return file_path;
            } else {
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }

        free(path_copy);

        if (stat(command, &buffer) == 0) {
            return command;
        }

        return NULL;
    }

    return NULL;
}

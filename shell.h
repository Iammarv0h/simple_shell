#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

/* Data structure to hold environment variables */
typedef struct {
    char **env;
} data_of_program;

/* Function prototypes */
int str_compare(const char *str1, const char *str2, int n);
int str_length(const char *str);
char *str_duplicate(const char *str);
char *str_concat(const char *str1, const char *str2);
void _print(const char *str);
char *env_get_key(const char *key, data_of_program *data);
int env_set_key(const char *key, const char *value, data_of_program *data);
int env_remove_key(const char *key, data_of_program *data);
void print_environ(data_of_program *data);

void builtin_exit(char *input);

#endif /* MAIN_H */

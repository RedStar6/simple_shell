#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct builtins
{
    char *function_desc;
    int (*function)();
} builtins;

extern char **environ;
int _strcmp(char *s1, char *s2);
int _putchar(char c);
void print_errorStartString(char **argv, int loopCount, char *command, char *error);
int u_exit(char **argv, char *command);
int builtin_functions(char **argv, char *command);

#endif /* HEADER_H */
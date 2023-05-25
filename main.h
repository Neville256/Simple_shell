#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

#define DELIM " \t\r\n\v\a"

extern char **environ;

char **command_split(char *);
void free_args(char **);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);
char *_getenv(char *);
int _strncmp(char *, char *, size_t);
char *int_to_str(int);
void command_error(char *, char *, int, int, int *);
void exit_error(char *, char **, int);
void exit_arguments(char **, char **, char *, int, int *, int *);
int _isdigit(char *);
int _atoi(char *);
void env_args(char **);
char *_strdup(const char *);

#endif

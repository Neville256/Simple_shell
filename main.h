#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* this will read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* these are commands used for chaining */
#define CMD_NORM 0
#define CMD_OR	1
#define CMD_AND	2
#define CMD_CHAIN 3

/* This will transform_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - linked list alone
 * @num: the requireds field number input
 * @str: a string of a variable
 * @next: carries over to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - arguments ot pass into function
 * function allows prototypes
 * pointer struct
 *@arg: contain arguments string produced
 *@argv: arguments of an array produced strings
 *@path: recent command of a string path
 *@argc: count the argument of a string array
 *@line_count: counts the error
 *@err_num: exit()s error code
 *@linecount_flag: input line count
 *@fname: filename program
 *@env: copy eviron linked list copies
 *@environ: LL env copy of envioron copy
 *@history: node history
 *@alias: node of the alias
 *@env_changed: changed environ
 *@status: last exec command returned
 *@cmd_buf: cmd_buf address to pointer, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: read line input for fd
 *@histcount: number count the history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT
/**
 * struct builtin - related function and contain of built string
 * @type: command flag builtin
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* root.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_functions_string_1.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* functions_string_1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* functions_string_2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* functions_string_3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, const char *src, int n);
char *_strchr(char *, char);

/*functions_string_4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* functions_memory_1.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void*, unsigned int, unsigned int);

/* functions_memory_2.c */
int bfree(void **);

/* functions_more.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* functions_more_2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*emulators_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/*emulators_builtin_2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline_1.c module */
void siginthandler(int sig_n);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void siginthandler(int);

/* info_1.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*env_1.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/*env_2.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* liststr_1.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* liststr_2.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain_1.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
#endif

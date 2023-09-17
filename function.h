#ifndef _FUNCTION_HEADER_FILE
#define _FUNCTION_HEADER_FILE

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct updatepass - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct updatepass 
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} update_p;

#define UPDATE_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(update_p *);
} builtin_submit;


/* Function protoype shel_looper.c */
int hsh(update_p *, char **);
int asset_builtin(update_p *);
void asset_cmd(update_p *);
void fork_cmd(update_p *);

/* Function protoype shel_monitor.c */
int mult_cmd(update_p *, char *);
char *dupli_chars(char *, int, int);
char *asset_path(update_p *, char *, char *);

/* Function protoype shel loophsh.c */
int loophsh(char **);

/* Function protoype 0-shel_errors.c */
void _funcputs(char *);
int _funcputchar(char ch);
int _putfildes(char chr, int fildes);
int _puts_fildes(char *strn, int fildes);

/* Function protoype 0-shel_string.c */
int _strlen_(char *);
int _strcmp_(char *, char *);
char *begin_on(const char *, const char *);
char *_strcat_(char *, char *);

/* Function protoype 1-shel_string.c */
char *_strcpy_(char *, char *);
char *_strdup_(const char *);
void _puts_(char *);
int _putchar(char);

/* Function protoype 0-shel_close.c */
char *_strncpy_(char *, char *, int);
char *_strncat_(char *, char *, int);
char *_strchr_(char *, char);

/* Function protoype shel_token.c */
char **strtop_k(char *, char *);
char **strto_k(char *, char);

/* Function protoype shel_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Function protoype shel_memory.c */
int bfree(void **);

/* Function protoype shel_atoi.c */
int opt_conjoint(update_p *);
int opt_deli(char, char *);
int opt_alphabet(int);
int opt_atoi(char *);

/* Function protoype 1-shel_errors.c */
int _erro_out(char *);
void show_error(update_p *, char *);
int show_dir(int, int);
char *change_numz(long int, int, int);
void take_out_comments(char *);

/* Function protoype 0-shel_builtin.c */
int _proexit(update_p *);
int _procd(update_p *);
int _prohelp(update_p *);

/* Function protoype 1-shel_builtin.c */
int _prohistory_(update_p *);
int _proalias_(update_p *);

/* Function protoype shel_getline.c */
ssize_t wax_input(update_p *);
int wax_get_line(update_p *, char **, size_t *);
void sigl_Handler(int);

/* Function protoype 0-shel_getupdate.c */
void remove_update(update_p *);
void make_update(update_p *, char **);
void discharge_update(update_p *, int);

/* Function protoype 0-shel_environ.c */
char *_getenv(update_p *, const char *);
int _myenv(update_p *);
int _mysetenv(update_p *);
int _myunsetenv(update_p *);
int populate_env_list(update_p *);

/* Function protoype 0-shel_proenvt.c */
char **get_environ(update_p *);
int _unsetenv(update_p *, char *);
int _setenv(update_p *, char *, char *);

/* Function protoype 0-shel_history.c */
char *get_history_file(update_p *update);
int write_history(update_p *update);
int read_history(update_p *update);
int build_history_list(update_p *update, char *bufa, int cordcount);
int renumber_history(update_p *update);

/* Function protoype 0-shel_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Function protoype 1-shel_lists.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Function protoype shel_variables.c */
int is_chain(update_p *, char *, size_t *);
void check_chain(update_p *, char *, size_t *, size_t, size_t);
int replace_alias(update_p *);
int replace_vars(update_p *);
int replace_string(char **, char *);

#endif


#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

/* Constants */
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64
#define MAX_PATH_SIZE 256
#define MAX_HISTORY_SIZE 100
#define SHELL_PROMPT "muShell$ "

/* Exit codes */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_COMMAND_NOT_FOUND 127

/* Token types for lexer */
typedef enum {
    TOKEN_WORD,          /* Regular command/argument */
    TOKEN_PIPE,          /* | */
    TOKEN_REDIRECT_OUT,  /* > */
    TOKEN_REDIRECT_APPEND, /* >> */
    TOKEN_REDIRECT_IN,   /* < */
    TOKEN_BACKGROUND,    /* & */
    TOKEN_EOF,           /* End of input */
    TOKEN_ERROR          /* Invalid token */
} token_type_t;

/* Token structure */
typedef struct {
    token_type_t type;
    char *value;
} token_t;

/* Command structure */
typedef struct command {
    char **args;             /* Command arguments (NULL terminated) */
    int argc;                /* Argument count */
    char *input_file;        /* Input redirection file */
    char *output_file;       /* Output redirection file */
    int append_output;       /* 1 if >>, 0 if > */
    int background;          /* 1 if background process */
    struct command *next;    /* Next command in pipeline */
} command_t;

/* Shell state structure */
typedef struct {
    char *input_buffer;
    char **history;
    int history_count;
    int history_index;
    char current_directory[MAX_PATH_SIZE];
    int last_exit_status;
    int running;
} shell_state_t;

/* Global shell state */
extern shell_state_t g_shell;

/* Function prototypes */

/* main.c */
int main(int argc, char **argv);
void shell_loop(void);
char *read_line(void);
void print_prompt(void);

/* lexer.c */
token_t *tokenize(const char *input, int *token_count);
void free_tokens(token_t *tokens, int count);
char *expand_variables(const char *input);

/* parser.c */
command_t *parse_command(token_t *tokens, int token_count);
void free_command(command_t *cmd);
int validate_syntax(token_t *tokens, int token_count);

/* executor.c */
int execute_command(command_t *cmd);
int execute_pipeline(command_t *cmd);
int execute_simple_command(command_t *cmd);

/* builtins.c */
int is_builtin(const char *command);
int execute_builtin(command_t *cmd);
int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_exit(char **args);
int builtin_help(char **args);
int builtin_export(char **args);
int builtin_env(char **args);

/* signals.c */
void setup_signals(void);
void sigint_handler(int sig);
void sigchld_handler(int sig);

/* history.c */
void init_history(void);
void add_to_history(const char *command);
void print_history(void);
char *get_history_item(int index);
void save_history(void);
void load_history(void);
void cleanup_history(void);

/* completion.c */
char **complete_filename(const char *text, int start, int end);
char **complete_command(const char *text, int start, int end);

/* redirection.c */
int setup_redirection(command_t *cmd);
void restore_stdio(int saved_stdin, int saved_stdout);

/* pipes.c */
int create_pipeline(command_t *cmd);
int setup_pipes(command_t *cmd);

/* utils.c */
char **split_string(const char *str, const char *delim);
void free_string_array(char **array);
char *trim_whitespace(char *str);
int count_commands_in_pipeline(command_t *cmd);
void error_exit(const char *message);
void print_error(const char *message);
char *get_executable_path(const char *command);

/* Debug macros */
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* Error handling macros */
#define HANDLE_ERROR(condition, message) \
    do { \
        if (condition) { \
            perror(message); \
            return EXIT_FAILURE; \
        } \
    } while (0)

#define SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            free(ptr); \
            ptr = NULL; \
        } \
    } while (0)

#endif /* SHELL_H */

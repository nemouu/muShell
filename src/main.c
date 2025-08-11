#include "shell.h"

/* Global shell state */
shell_state_t g_shell;

/**
 * Main entry point for muShell
 */
int main(int argc, char **argv) {
    (void)argc; /* Suppress unused parameter warning */
    (void)argv; /* Suppress unused parameter warning */
    
    /* Initialize shell state */
    memset(&g_shell, 0, sizeof(shell_state_t));
    g_shell.running = 1;
    g_shell.last_exit_status = 0;
    
    /* Get current working directory */
    if (getcwd(g_shell.current_directory, sizeof(g_shell.current_directory)) == NULL) {
        perror("getcwd");
        strcpy(g_shell.current_directory, "/");
    }
    
    /* Setup signal handlers */
    setup_signals();
    
    /* Initialize history */
    init_history();
    
    /* Print welcome message */
    printf("Welcome to muShell - A Minimalist Unix Shell\n");
    printf("Type 'help' for available commands or 'exit' to quit.\n\n");
    
    /* Main shell loop */
    shell_loop();
    
    /* Cleanup */
    cleanup_history();
    SAFE_FREE(g_shell.input_buffer);
    
    printf("Goodbye!\n");
    return g_shell.last_exit_status;
}

/**
 * Main shell loop - Read, Evaluate, Print Loop (REPL)
 */
void shell_loop(void) {
    char *line;
    token_t *tokens;
    command_t *cmd;
    int token_count;
    
    while (g_shell.running) {
        /* Print prompt and read input */
        print_prompt();
        line = read_line();
        
        /* Check for EOF (Ctrl+D) */
        if (line == NULL) {
            printf("\n");
            break;
        }
        
        /* Skip empty lines */
        if (strlen(line) == 0) {
            SAFE_FREE(line);
            continue;
        }
        
        /* Add to history (if not empty) */
        add_to_history(line);
        
        /* Tokenize input */
        tokens = tokenize(line, &token_count);
        if (tokens == NULL) {
            print_error("Failed to tokenize input");
            SAFE_FREE(line);
            continue;
        }
        
        /* Parse tokens into command structure */
        cmd = parse_command(tokens, token_count);
        if (cmd == NULL) {
            print_error("Failed to parse command");
            free_tokens(tokens, token_count);
            SAFE_FREE(line);
            continue;
        }
        
        /* Execute command */
        g_shell.last_exit_status = execute_command(cmd);
        
        /* Cleanup */
        free_command(cmd);
        free_tokens(tokens, token_count);
        SAFE_FREE(line);
    }
}

/**
 * Read a line of input from the user
 * Returns allocated string that must be freed by caller
 */
char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;
    
    /* Use getline for robust input reading */
    chars_read = getline(&line, &bufsize, stdin);
    
    /* Handle EOF or error */
    if (chars_read == -1) {
        SAFE_FREE(line);
        return NULL;
    }
    
    /* Remove trailing newline */
    if (chars_read > 0 && line[chars_read - 1] == '\n') {
        line[chars_read - 1] = '\0';
    }
    
    return line;
}

/**
 * Print the shell prompt
 */
void print_prompt(void) {
    /* Use different prompt colors for debug vs release */
    #ifdef DEBUG
        printf("\033[1;32m%s\033[0m", SHELL_PROMPT); /* Green for debug */
    #else
        printf("%s", SHELL_PROMPT);
    #endif
    
    fflush(stdout);
}

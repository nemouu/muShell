#include "shell.h"

/**
 * Split a string into an array of strings using delimiter
 * Returns NULL-terminated array that must be freed with free_string_array()
 */
char **split_string(const char *str, const char *delim) {
    if (!str || !delim) return NULL;
    
    char *str_copy = strdup(str);
    if (!str_copy) return NULL;
    
    char **result = malloc(MAX_TOKENS * sizeof(char*));
    if (!result) {
        free(str_copy);
        return NULL;
    }
    
    int count = 0;
    char *token = strtok(str_copy, delim);
    
    while (token && count < MAX_TOKENS - 1) {
        result[count] = strdup(token);
        if (!result[count]) {
            /* Cleanup on failure */
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            free(str_copy);
            return NULL;
        }
        count++;
        token = strtok(NULL, delim);
    }
    
    result[count] = NULL; /* NULL terminate */
    free(str_copy);
    return result;
}

/**
 * Free a NULL-terminated array of strings
 */
void free_string_array(char **array) {
    if (!array) return;
    
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

/**
 * Trim leading and trailing whitespace from a string
 * Modifies the string in place and returns pointer to trimmed string
 */
char *trim_whitespace(char *str) {
    if (!str) return NULL;
    
    /* Trim leading whitespace */
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')) {
        str++;
    }
    
    /* Handle empty string */
    if (*str == '\0') return str;
    
    /* Trim trailing whitespace */
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    *(end + 1) = '\0';
    
    return str;
}

/**
 * Count the number of commands in a pipeline
 */
int count_commands_in_pipeline(command_t *cmd) {
    int count = 0;
    while (cmd) {
        count++;
        cmd = cmd->next;
    }
    return count;
}

/**
 * Print error message and exit
 */
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * Print error message to stderr without exiting
 */
void print_error(const char *message) {
    fprintf(stderr, "muShell: %s\n", message);
}

/**
 * Find executable in PATH
 * Returns allocated string with full path, or NULL if not found
 */
char *get_executable_path(const char *command) {
    if (!command) return NULL;
    
    /* If command contains '/', use it as-is */
    if (strchr(command, '/')) {
        if (access(command, X_OK) == 0) {
            return strdup(command);
        }
        return NULL;
    }
    
    /* Search in PATH */
    char *path_env = getenv("PATH");
    if (!path_env) return NULL;
    
    char *path_copy = strdup(path_env);
    if (!path_copy) return NULL;
    
    char *dir = strtok(path_copy, ":");
    char *full_path = malloc(MAX_PATH_SIZE);
    
    if (!full_path) {
        free(path_copy);
        return NULL;
    }
    
    while (dir) {
        snprintf(full_path, MAX_PATH_SIZE, "%s/%s", dir, command);
        
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        
        dir = strtok(NULL, ":");
    }
    
    free(path_copy);
    free(full_path);
    return NULL;
}

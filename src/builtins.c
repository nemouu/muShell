#include "shell.h"

int is_builtin(const char *command) {
    /* TODO: Implement in Phase 5 */
    (void)command;
    return 0;
}

int execute_builtin(command_t *cmd) {
    /* TODO: Implement in Phase 5 */
    (void)cmd;
    return 0;
}

int builtin_cd(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    return 0;
}

int builtin_pwd(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    return 0;
}

int builtin_exit(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    g_shell.running = 0;
    return 0;
}

int builtin_help(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    return 0;
}

int builtin_export(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    return 0;
}

int builtin_env(char **args) {
    /* TODO: Implement in Phase 5 */
    (void)args;
    return 0;
}

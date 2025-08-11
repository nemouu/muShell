#include "shell.h"

void init_history(void) {
    /* TODO: Implement in Phase 9 */
    g_shell.history = malloc(MAX_HISTORY_SIZE * sizeof(char*));
    g_shell.history_count = 0;
    g_shell.history_index = 0;
}

void add_to_history(const char *command) {
    /* TODO: Implement in Phase 9 */
    (void)command;
}

void print_history(void) {
    /* TODO: Implement in Phase 9 */
    printf("History not yet implemented\n");
}

char *get_history_item(int index) {
    /* TODO: Implement in Phase 9 */
    (void)index;
    return NULL;
}

void save_history(void) {
    /* TODO: Implement in Phase 9 */
}

void load_history(void) {
    /* TODO: Implement in Phase 9 */
}

void cleanup_history(void) {
    /* TODO: Implement in Phase 9 */
    if (g_shell.history) {
        for (int i = 0; i < g_shell.history_count; i++) {
            SAFE_FREE(g_shell.history[i]);
        }
        SAFE_FREE(g_shell.history);
    }
}

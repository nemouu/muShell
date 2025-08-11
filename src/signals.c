#include "shell.h"

void setup_signals(void) {
    /* TODO: Implement in Phase 8 */
    /* Basic signal setup for now */
    signal(SIGINT, sigint_handler);
}

void sigint_handler(int sig) {
    /* TODO: Implement in Phase 8 */
    (void)sig;
    printf("\n");
    print_prompt();
    fflush(stdout);
}

void sigchld_handler(int sig) {
    /* TODO: Implement in Phase 8 */
    (void)sig;
}
